;
; Microcontroladores Actividad 2.asm
;
; Created: 28/09/2025 08:39:21 p. m.
; Author : juanc
;

; =============================================================
; Actividad II - Microcontroladores ATmega328P
; Generar n n�meros en orden descendente y convertirlos a decimal
; =============================================================

.include "m328pdef.inc"

; =============================================================
; DEFINICIONES Y VARIABLES
; =============================================================
.def n = r16           ; Registro para el valor de n
.def counter = r17     ; Contador para bucles
.def temp = r18        ; Registro temporal
.def decenas = r19     ; Registro para d�gito de decenas
.def unidades = r20    ; Registro para d�gito de unidades

.equ INI_DIR = 0x120   ; Direcci�n inicial para n�meros hexadecimales
.equ DEC_DIR = 0x200   ; Direcci�n inicial para n�meros decimales

; =============================================================
; VECTOR DE RESET
; =============================================================
.cseg
.org 0x0000
    jmp main

; =============================================================
; PROGRAMA PRINCIPAL
; =============================================================
main:
    ; Inicializar Stack Pointer
    ldi temp, high(RAMEND)
    out SPH, temp
    ldi temp, low(RAMEND)
    out SPL, temp

    ; Configurar valor de n (ejemplo: n=15)
    ldi n, 15

    ; Generar n�meros en orden descendente
    rcall generar_numeros

    ; Convertir n�meros a formato decimal
    rcall convertir_decimal

    ; Fin del programa - bucle infinito
fin:
    rjmp fin

; =============================================================
; SUBRUTINA: GENERAR N�MEROS EN ORDEN DESCENDENTE
; =============================================================
; Descripci�n: Genera n n�meros en orden descendente y los almacena
; en memoria SRAM a partir de la direcci�n 0x120
; =============================================================
generar_numeros:
    ; Inicializar puntero X con direcci�n inicial
    ldi XL, low(INI_DIR)
    ldi XH, high(INI_DIR)
    
    ; Inicializar contador y valor inicial
    mov counter, n
    mov temp, n
    
generar_loop:
    ; Almacenar n�mero en memoria
    st X+, temp
    
    ; Decrementar valor
    dec temp
    
    ; Decrementar contador y verificar si continuar
    dec counter
    brne generar_loop
    
    ; Almacenar el �ltimo valor (0)
    st X, temp
    
    ret

; =============================================================
; SUBRUTINA: CONVERTIR A FORMATO DECIMAL
; =============================================================
; Descripci�n: Convierte los n�meros hexadecimales a formato decimal
; y los almacena en memoria SRAM a partir de la direcci�n 0x200
; =============================================================
convertir_decimal:
    ; Inicializar puntero X para lectura (datos originales)
    ldi XL, low(INI_DIR)
    ldi XH, high(INI_DIR)
    
    ; Inicializar puntero Y para escritura (datos decimales)
    ldi YL, low(DEC_DIR)
    ldi YH, high(DEC_DIR)
    
    ; Inicializar contador
    mov counter, n
    inc counter          ; n+1 elementos (incluye el 0)

convertir_loop:
    ; Cargar n�mero desde memoria
    ld temp, X+
    
    ; Convertir a decimal
    rcall hex_a_decimal
    
    ; Almacenar d�gitos en memoria
    st Y+, decenas
    st Y+, unidades
    
    ; Decrementar contador y verificar si continuar
    dec counter
    brne convertir_loop
    
    ret

; =============================================================
; SUBRUTINA: CONVERSI�N HEXADECIMAL A DECIMAL
; =============================================================
; Descripci�n: Convierte un n�mero hexadecimal (0-99) a sus
; d�gitos decimales correspondientes
; Entrada: temp - n�mero a convertir (0x00-0x63)
; Salida: decenas - d�gito de decenas (0-9)
;         unidades - d�gito de unidades (0-9)
; =============================================================
hex_a_decimal:
    push temp
    push counter
    
    ; Inicializar decenas
    ldi decenas, 0
    
calcular_decenas:
    ; Verificar si el n�mero es menor que 10
    cpi temp, 10
    brlo calcular_unidades
    
    ; Restar 10 y aumentar contador de decenas
    subi temp, 10
    inc decenas
    rjmp calcular_decenas

calcular_unidades:
    ; El resto son las unidades
    mov unidades, temp
    
    pop counter
    pop temp
    ret

; =============================================================
; FIN DEL PROGRAMA
; =============================================================