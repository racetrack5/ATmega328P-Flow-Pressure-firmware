/* Speed of MCU in Hz. */
#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

uint16_t sample_f1031v();
uint8_t sample_mpx5700();

void init_lcd();

void init_adc();

void forward_bit_address(uint8_t *byte);
void send_data_lcd(uint8_t byte);
void send_command_lcd(uint8_t byte);

uint8_t receive_data_i2c();
void send_slaveaddr_i2c();
void send_start_i2c();
void init_i2c();