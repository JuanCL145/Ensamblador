/*
 * config.h
 *
 * Created: 14/12/2025 02:40:05 p. m.
 *  Author: HP
 */ 


#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define ADC_CHANNEL 0

// Pines
#define INTERRUPT_PIN PD2  // INT0
#define LED_PIN PB0

// Dirección I2C del sensor LM75
#define LM75_ADDRESS 0x48

#endif