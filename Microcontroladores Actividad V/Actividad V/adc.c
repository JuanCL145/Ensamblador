/*
 * CFile1.c
 *
 * Created: 14/12/2025 02:39:04 p. m.
 *  Author: HP
 */ 

#include "adc.h"
#include "config.h"

void adc_init(void) {
	// Configurar AVCC como referencia, ajustar a la izquierda
	ADMUX = (1 << REFS0);
	
	// Habilitar ADC, prescaler 128 (para 16MHz -> 125KHz)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t channel) {
	// Seleccionar canal
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	// Iniciar conversión
	ADCSRA |= (1 << ADSC);
	
	// Esperar a que termine la conversión
	while (ADCSRA & (1 << ADSC));
	
	// Retornar valor
	return ADC;
}

void adc_start_conversion(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1 << ADSC);
}

uint8_t adc_conversion_complete(void) {
	return !(ADCSRA & (1 << ADSC));
}