#include "main.h"

void LCD_WRT(uint8_t BYTE)
{
    if(BYTE & 0x10)
        PORTB |= (1 << 0);
    else
        PORTB &= ~(1 << 0);

    if(BYTE & 0x20)
        PORTB |= (1 << 1);
    else
        PORTB &= ~(1 << 1);

    if(BYTE & 0x40)
        PORTB |= (1 << 2);
    else
        PORTB &= ~(1 << 2);

    if(BYTE & 0x80)
        PORTB |= (1 << 3);
    else
        PORTB &= ~(1 << 3);
}

void LCD_STR(uint8_t* STR)
{
    uint16_t i = 0;
    while((*STR)!='\0')
    {
        LCD_DAT(*STR);
        STR++; // +1 to ptr address
    }
} 

void LCD_DAT(uint8_t BYTE)
{
    LCD_WRT(BYTE); // Upper nibble (4 bits)
    
    PORTD |= (1 << 3); // RS=1
    PORTD |= (1 << 5); // EN=1
    _delay_us(1);
    PORTD &= ~(1 << 5); // sEN=0  
    _delay_us(200);

    BYTE <<= 4; // Shift lower bits

    LCD_WRT(BYTE); // Upper nibble (4 bits)
    
    PORTD |= (1 << 5);
    _delay_us(1);
    PORTD &= ~(1 << 5);
    _delay_us(200);
}

void LCD_CMD(uint8_t BYTE)
{
    LCD_WRT(BYTE); // Upper nibble (4 bits)

    PORTD &= ~(1 << 3); // RS=0
    PORTD|=(1 << 5); // EN=1    
    _delay_us(1);
    PORTD &= ~(1 << 5); // EN=0  
    _delay_ms(2);

    BYTE <<= 4; // Shift lower bits

    LCD_WRT(BYTE); // Lower nibble (4 bits)
    
    PORTD |= (1 << 5);
    _delay_us(1);
    PORTD &= ~(1 << 5);
    _delay_ms(2);
}

void LCD_INIT()
{
    // Cycle LCD data and power pins
    DDRB = 0x00;
    DDRD = 0x00;
    DDRC &= ~(1 << 6);
    PORTC &= ~(1 << 6);

    _delay_ms(1000);
  
    DDRB = 0xFF;
    DDRD = 0xFF;
    DDRD |= (1 << 6);
    PORTD |= (1 << 6);
    
    // Delay for power-on
    _delay_ms(1000);
    
    LCD_CMD(0x02); // 4-bit
    LCD_CMD(0x28); // 4-bit, 2-line, char size
    LCD_CMD(0x0C); // Display on, cursor off
}
