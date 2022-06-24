/* Speed of MCU in Hz. */
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>>
#include <string.h>
#include <util/delay.h>

uint16_t sample_f1031v();
uint8_t sample_mpx5700();

void report_data();

uint8_t receive_data_i2c();
void send_slaveaddr_i2c();
void send_start_i2c();
void init_i2c();

void init_adc();

void forward_bit_address(uint8_t *byte);
void send_data_lcd(uint8_t byte);
void send_command_lcd(uint8_t byte);
void init_lcd();