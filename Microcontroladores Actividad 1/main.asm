;
; Microcontroladores Actividad 1.asm
;
; Created: 16/09/2025 08:43:13 p. m.
; Author : JuanCCL
;


; Replace with your application code
start:

.include "m328pdef.inc"

.cseg
.org 0

; Configuración de pines
ldi r16, (0<<DDD2) | (0<<DDD3)   ; PD2 y PD3 como entradas
out DDRD, r16
ldi r16, (1<<PORTD2) | (1<<PORTD3) ; Activar pull-up en PD2 y PD3
out PORTD, r16

; Configurar PB5 como salida
sbi DDRB, 5   ; PB5 como salida

main:
  ; Leer entradas
  in r18, PIND
  andi r18, (1<<PIND2)|(1<<PIND3)
  mov r19, r18
  lsr r19
  lsr r19       ; r19 tiene el valor de entrada (0,1,2,3)

  ; Selección de frecuencia based on entradas
  cpi r19, 0
  brne next1
  call delay5kHz   ; 5 kHz
  rjmp next_end
next1:
  cpi r19, 1
  brne next2
  ldi r17, 79      ; 25 kHz
  call delay
  rjmp next_end
next2:
  cpi r19, 2
  brne next3
  ldi r17, 33      ; 60 kHz
  call delay
  rjmp next_end
next3:
  ldi r17, 25      ; 80 kHz
  call delay
next_end:
  sbi PINB, 5      ; Alternar PB5
  rjmp main

; Rutina de retardo para 5 kHz (aproximadamente 1600 ciclos)
delay5kHz:
    ldi r21, 90
outer5:
    ldi r22, 5
inner5:
    dec r22
    brne inner5
    dec r21
    brne outer5
    ret

; Rutina de retardo para otras frecuencias (usando r17)
delay:
    mov r20, r17
delay_loop:
    dec r20
    brne delay_loop
    ret