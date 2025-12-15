/*
 * Actividad V.c
 *
 * Created: 14/12/2025 02:10:09 p. m.
 * Author : HP
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "config.h"
#include "adc.h"
#include "i2c.h"
#include "usart.h"
#include "interrupts.h"

// Variables globales
volatile uint16_t adc_value = 0;
volatile uint8_t adc_ready = 0;

// ISR para conversión ADC completa
ISR(ADC_vect) {
	adc_value = ADC;
	adc_ready = 1;
}

void system_init(void) {
	// Inicializar todos los módulos
	usart_init(BAUD_RATE);
	adc_init();
	i2c_init();
	interrupt_init();
	
	// Habilitar interrupciones globales
	enable_global_interrupts();
	
	// Configurar LED como salida
	DDRB |= (1 << LED_PIN);
	PORTB &= ~(1 << LED_PIN);
	
	// Habilitar interrupción por ADC
	ADCSRA |= (1 << ADIE);
	
	usart_print_string("Sistema Iniciado...\r\n");
}

int main(void) {
	uint8_t counter = 0;
	float temperature = 0.0;
	
	system_init();
	
	while (1) {
		// Leer ADC cada 100ms
		if (counter % 10 == 0) {  // 10 * 10ms = 100ms
			adc_start_conversion(ADC_CHANNEL);
			
			// Esperar conversión o usar polling
			while (!adc_conversion_complete());
			adc_value = adc_read(ADC_CHANNEL);
			
			usart_print_string("ADC: ");
			usart_print_number(adc_value);
			usart_print_string("\r\n");
			
			// Leer temperatura I2C cada segundo
			if (counter % 100 == 0) {  // 100 * 10ms = 1000ms
				temperature = read_lm75_temperature();
				usart_print_string("Temp I2C: ");
				usart_print_float(temperature, 1);
				usart_print_string("°C\r\n");
			}
		}
		
		// Verificar interrupción externa
		if (interrupt_flag) {
			usart_print_string("Interrupcion externa detectada!\r\n");
			
			// Toggle LED
			PORTB ^= (1 << LED_PIN);
			
			interrupt_flag = 0;
		}
		
		_delay_ms(10);  // Delay base de 10ms
		counter++;
		
		if (counter >= 100) counter = 0;  // Reset contador cada segundo
	}
	
	return 0;
}

