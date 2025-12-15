/*
 * IncFile1.h
 *
 * Created: 14/12/2025 02:36:53 p. m.
 *  Author: HP
 */ 


#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <stdio.h>

void usart_init(uint32_t baud);
void usart_transmit(uint8_t data);
uint8_t usart_receive(void);
void usart_print_string(const char* str);
void usart_print_number(uint16_t num);
void usart_print_float(float num, uint8_t decimals);

#endif