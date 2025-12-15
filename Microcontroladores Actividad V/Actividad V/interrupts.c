/*
 * CFile1.c
 *
 * Created: 14/12/2025 02:34:24 p. m.
 *  Author: HP
 */ 

#include "interrupts.h"
#include "config.h"

volatile uint8_t interrupt_flag = 0;

void interrupt_init(void) {
	// Configurar INT0 en flanco descendente
	EICRA |= (1 << ISC01);  // Flanco descendente
	EICRA &= ~(1 << ISC00);
	
	// Habilitar INT0
	EIMSK |= (1 << INT0);
	
	// Configurar PD2 como entrada
	DDRD &= ~(1 << INTERRUPT_PIN);
	PORTD |= (1 << INTERRUPT_PIN);  // Pull-up interno
}

void enable_global_interrupts(void) {
	sei();
}

// Rutina de servicio de interrupción para INT0
ISR(INT0_vect) {
	interrupt_flag = 1;
}