/*
 * i2c.c
 *
 * Created: 14/12/2025 02:37:56 p. m.
 *  Author: HP
 */ 

#include "i2c.h"
#include "config.h"
#include <util/delay.h>

void i2c_init(void) {
	// Configurar velocidad SCL = F_CPU/(16 + 2*TWBR*prescaler)
	// Para 100kHz @ 16MHz: TWBR = 72, prescaler = 1
	TWSR = 0x00;  // Prescaler = 1
	TWBR = 0x48;  // TWBR = 72
	TWCR = (1 << TWEN);  // Habilitar TWI
}

uint8_t i2c_start(uint8_t address) {
	// Enviar condición START
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	// Esperar a que se complete
	while (!(TWCR & (1 << TWINT)));
	
	// Verificar código de estado
	if ((TWSR & 0xF8) != I2C_START && (TWSR & 0xF8) != I2C_REP_START)
	return 0;
	
	// Enviar dirección + escritura
	TWDR = (address << 1);
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	while (!(TWCR & (1 << TWINT)));
	
	if ((TWSR & 0xF8) != I2C_MT_SLA_ACK)
	return 0;
	
	return 1;
}

uint8_t i2c_write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	while (!(TWCR & (1 << TWINT)));
	
	return (TWSR & 0xF8) == I2C_MT_DATA_ACK;
}

uint8_t i2c_read_ack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t i2c_read_nack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void i2c_stop(void) {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	_delay_us(100);
}

uint8_t i2c_read_register(uint8_t dev_addr, uint8_t reg_addr) {
	uint8_t data = 0;
	
	if (i2c_start(dev_addr)) {
		i2c_write(reg_addr);
		i2c_start(dev_addr | 0x01);  // Modo lectura
		data = i2c_read_nack();
		i2c_stop();
	}
	
	return data;
}

void i2c_write_register(uint8_t dev_addr, uint8_t reg_addr, uint8_t data) {
	if (i2c_start(dev_addr)) {
		i2c_write(reg_addr);
		i2c_write(data);
		i2c_stop();
	}
}

float read_lm75_temperature(void) {
	uint8_t msb, lsb;
	int16_t raw_temp;
	float temperature;
	
	if (i2c_start(LM75_ADDRESS)) {
		i2c_write(0x00);  // Registro de temperatura
		
		// RE-start para lectura
		i2c_start(LM75_ADDRESS | 0x01);
		
		msb = i2c_read_ack();
		lsb = i2c_read_nack();
		
		i2c_stop();
		
		raw_temp = (msb << 8) | lsb;
		raw_temp >>= 7;  // LM75 tiene 9 bits de resolución
		
		temperature = raw_temp * 0.5;  // Cada bit = 0.5°C
		return temperature;
	}
	
	return -999.0;  // Error
}