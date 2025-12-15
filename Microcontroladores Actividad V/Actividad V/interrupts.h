/*
 * IncFile1.h
 *
 * Created: 14/12/2025 02:35:36 p. m.
 *  Author: HP
 */ 

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <avr/io.h>
#include <avr/interrupt.h>

void interrupt_init(void);
void enable_global_interrupts(void);

extern volatile uint8_t interrupt_flag;

#endif