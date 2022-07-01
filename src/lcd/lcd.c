#include "main.h"

static void write_nibble(uint8_t byte)
{
    /* Test most significant 4-bits and set pins. */
    if(byte & 0x10)
        LCD_DATA_PORT |=  (1 << LCD_DATA_PIN1);
    else
        LCD_DATA_PORT &= ~(1 << LCD_DATA_PIN1);

    if(byte & 0x20)
        LCD_DATA_PORT |=  (1 << LCD_DATA_PIN2);
    else
        LCD_DATA_PORT &= ~(1 << LCD_DATA_PIN2);

    if(byte & 0x40)
        LCD_DATA_PORT |=  (1 << LCD_DATA_PIN3);
    else
        LCD_DATA_PORT &= ~(1 << LCD_DATA_PIN3);

    if(byte & 0x80)
        LCD_DATA_PORT |=  (1 << LCD_DATA_PIN4);
    else
        LCD_DATA_PORT &= ~(1 << LCD_DATA_PIN4);
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
    /* Send data to LCD. */
    write_nibble(byte);
    
    LCD_CONTROL_PORT |=  (1 << LCD_RS_PIN)|(1 << LCD_EN_PIN);
    _delay_us(1);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN_PIN);
    _delay_us(2);

    byte <<= 4;

    write_nibble(byte);

    LCD_CONTROL_PORT |=  (1 << LCD_EN_PIN);
    _delay_us(1);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN_PIN);
    _delay_us(5);
}

void send_command_lcd(uint8_t byte)
{
    /* Send command to LCD. */
    write_nibble(byte);

    LCD_CONTROL_PORT &= ~(1 << LCD_RS_PIN);
    LCD_CONTROL_PORT |=  (1 << LCD_EN_PIN);  
    _delay_us(1);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN_PIN);
    _delay_us(2);

    byte <<= 4;

    write_nibble(byte);
    
    LCD_CONTROL_PORT |=  (1 << LCD_EN_PIN);
    _delay_us(1);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN_PIN);
    _delay_us(5);
}

void init_lcd(void)
{
    /* Cycle both power and data pins with generous
     * delays to ensure reliability.
     */
    DDRB, DDRD = 0x00;
    LCD_POWER_PORT &=  ~(1 << LCD_POWER_PIN);

    _delay_ms(500);
  
    DDRB, DDRD = 0xFF;
    LCD_CONTROL_PORT |= (1 << LCD_POWER_PIN);

    _delay_ms(500);
    
    /* Enable 4-bit mode with 2-lines. */
    send_command_lcd(0x02);
    send_command_lcd(0x28);
    send_command_lcd(0x0C);
}