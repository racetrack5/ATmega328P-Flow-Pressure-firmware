#include "main.h"

static void report_data_usart(uint16_t f1031v, uint16_t mpx5700)
{
    char buffer[16];
    int8_t *ptr = &buffer;

    memcpy(buffer, (char)f1031v + " L/min (STP)", 16);
    while(*ptr > 0)
    {
        xmit_usart(*ptr);
        while(!(UCSR0A & (1 << UDRE0))) ; /* Wait for previous byte. */
        ptr++; /* Next byte to send. */
    }

    memcpy(buffer, (char)mpx5700 + " cmH2O", 16);
    while(*ptr > 0)
    {
        xmit_usart(*ptr);
        while(!(UCSR0A & (1 << UDRE0))) ;
        ptr++;
    }
}

static void report_data_lcd(uint16_t f1031v, uint16_t mpx5700)
{
    char buffer[16];
    int8_t *ptr = &buffer;

    /* Cursor return. */
    send_command_lcd(0x80);
    _delay_ms(2);

    /* Report flows from F1031V sensor. */
    memcpy(buffer, (char)f1031v + " L/min (STP)", 16);
    forward_bit_address(ptr);

    /* Next line. */
    send_command_lcd(0xC0);

    /* Report pressures from MPX5700 sensor. */
    memcpy(buffer, (char)mpx5700 + " cmH2O", 16);
    forward_bit_address(ptr);
}

void report_data(void)
{
    int16_t f1031v = sample_f1031v();
    int16_t mpx5700 = sample_mpx5700();

    report_data_lcd(f1031v, mpx5700);
    report_data_usart(f1031v, mpx5700);
}