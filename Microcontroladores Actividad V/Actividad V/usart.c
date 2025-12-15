/*
 * CFile1.c
 *
 * Created: 14/12/2025 02:36:04 p. m.
 *  Author: HP
 */ 

#include "usart.h"
#include "config.h"

void usart_init(uint32_t baud) {
	uint16_t ubrr = F_CPU / 16 / baud - 1;
	
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // 8 bits, 1 stop, sin paridad
}

void usart_transmit(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

uint8_t usart_receive(void) {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void usart_print_string(const char* str) {
	while (*str) {
		usart_transmit(*str++);
	}
}

void usart_print_number(uint16_t num) {
	char buffer[10];
	sprintf(buffer, "%u", num);
	usart_print_string(buffer);
}

void usart_print_float(float num, uint8_t decimals) {
	char buffer[20];
	dtostrf(num, 4, decimals, buffer);
	usart_print_string(buffer);
}