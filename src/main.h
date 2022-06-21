/* Speed of MCU in Hz. */
#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

void forward_bit_address(uint8_t *byte);
void send_data_lcd(uint8_t byte);
void send_command_lcd(uint8_t byte);

void sample_f1031v();

void init_lcd();

void poll_adc();
void init_adc();

uint8_t receive_data_i2c(uint8_t xmit);
uint8_t send_slaveaddr_i2c(uint8_t mode);
uint8_t send_start_i2c();
uint8_t reply_i2c(uint8_t xmit);
void wait_i2c();
void init_i2c();