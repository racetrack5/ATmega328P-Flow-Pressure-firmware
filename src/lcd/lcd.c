#include "main.h"

static void write_nibble(uint8_t byte)
{
    /* Test most significant 4-bits and set pins */
    if(byte & 0x10)
        PORTB |= (1 << 0);
    else
        PORTB &= ~(1 << 0);

    if(byte & 0x20)
        PORTB |= (1 << 1);
    else
        PORTB &= ~(1 << 1);

    if(byte & 0x40)
        PORTB |= (1 << 2);
    else
        PORTB &= ~(1 << 2);

    if(byte & 0x80)
        PORTB |= (1 << 3);
    else
        PORTB &= ~(1 << 3);
}

void forward_bit_address(uint8_t *byte)
{
    /* Forward address of each bit to the LCD */
    while((*byte)!='\0')
    {
        send_data_lcd(*byte);
        byte++;
    }
} 

void send_data_lcd(uint8_t byte)
{
    /* Send data (not commands) to the LCD. The LCD
     * is operating in 4-bit mode (to conserve pins).
     */
    write_nibble(byte);
    
    PORTD |= (1 << 3);
    PORTD |= (1 << 5);
    _delay_us(1);
    PORTD &= ~(1 << 5);
    _delay_us(200);

    /* Shift LSBs rightward (send second lot of
     * 4 bits (nibble).
     */
    byte <<= 4;

    write_nibble(byte);
    
    PORTD |= (1 << 5);
    _delay_us(1);
    PORTD &= ~(1 << 5);
    _delay_us(200);
}

void send_command_lcd(uint8_t byte)
{
    /* Send command to LCD. Looser timings compared to
     * simply sending data, otherwise LCD we risk the
     * LCD not initialising correctly (garbled text).
     */
    write_nibble(byte);

    PORTD &= ~(1 << 3);
    PORTD|=(1 << 5);  
    _delay_us(1);
    PORTD &= ~(1 << 5);
    _delay_ms(2);

    byte <<= 4;

    write_nibble(byte);
    
    PORTD |= (1 << 5);
    _delay_us(1);
    PORTD &= ~(1 << 5);
    _delay_ms(2);
}

void init_lcd()
{
    /* Cycle both power and data pins with generous
     * delays to ensure reliability.
     */
    DDRB = 0x00;
    DDRD = 0x00;
    DDRC &= ~(1 << 6);
    PORTC &= ~(1 << 6);

    _delay_ms(1000);
  
    DDRB = 0xFF;
    DDRD = 0xFF;
    DDRD |= (1 << 6);
    PORTD |= (1 << 6);

    _delay_ms(1000);
    
    /* Enable 4-bit mode with 2-lines. */
    send_command_lcd(0x02);
    send_command_lcd(0x28);
    send_command_lcd(0x0C);
}