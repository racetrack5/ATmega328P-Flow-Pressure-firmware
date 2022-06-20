#include <avr/io.h>
#include <string.h>

#define F_CPU 16000000 // Speed of MCU in Hz
#include <util/delay.h>

// LCD
void LCD_WRT(uint8_t BYTE);
void LCD_STR(uint8_t* STR);
void LCD_DAT(uint8_t BYTE);
void LCD_CMD(uint8_t BYTE);

void LCD_INIT();

// I2C
void I2C_INIT();

// ADC
void ADC_INIT();
