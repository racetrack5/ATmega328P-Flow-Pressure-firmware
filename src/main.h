/* Speed of MCU in Hz. */
#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

/* Physical connections to LCD. */
#define LCD_POWER_PORT      PORTD
#define LCD_POWER_PIN       PORTD6
#define LCD_CONTROL_PORT    PORTD
#define LCD_RS_PIN          PORTD3
#define LCD_EN_PIN          PORTD5
#define LCD_DATA_PORT       PORTB
#define LCD_DATA_PIN1       PORTB0
#define LCD_DATA_PIN2       PORTB1
#define LCD_DATA_PIN3       PORTB2
#define LCD_DATA_PIN4       PORTB3

uint16_t sample_f1031v(void);
uint16_t sample_mpx5700(void);

void report_data(void);

uint8_t return_overflows(void);
void zero_overflows(void);
void init_timer(void);

void send_slaveaddr_i2c(void);
void send_start_i2c(void);
void init_i2c(void);

void init_adc(void);

uint8_t isrchk_usart(void);
uint8_t return_usart(void);
void xmit_usart(uint8_t byte);
void init_usart(uint16_t baud_rate);

void forward_bit_address(uint8_t *byte);
void send_data_lcd(uint8_t byte);
void send_command_lcd(uint8_t byte);
void init_lcd(void);