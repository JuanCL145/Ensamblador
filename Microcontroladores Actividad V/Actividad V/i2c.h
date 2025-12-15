/*
 * IncFile1.h
 *
 * Created: 14/12/2025 02:38:17 p. m.
 *  Author: HP
 */ 


#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

#define I2C_START 0x08
#define I2C_REP_START 0x10
#define I2C_MT_SLA_ACK 0x18
#define I2C_MT_DATA_ACK 0x28
#define I2C_MR_SLA_ACK 0x40
#define I2C_MR_DATA_ACK 0x50
#define I2C_MR_DATA_NACK 0x58

void i2c_init(void);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
void i2c_stop(void);
uint8_t i2c_read_register(uint8_t dev_addr, uint8_t reg_addr);
void i2c_write_register(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
float read_lm75_temperature(void);

#endif