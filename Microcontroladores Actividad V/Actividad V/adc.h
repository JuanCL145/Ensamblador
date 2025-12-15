/*
 * adc.h
 *
 * Created: 14/12/2025 02:39:36 p. m.
 *  Author: HP
 */ 


#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void adc_init(void);
uint16_t adc_read(uint8_t channel);
void adc_start_conversion(uint8_t channel);

#endif