#include "main.h"

void report_data()
{
    /* Grab up-to-date sensor data and send to LCD. */
    int16_t f1031v;
    int16_t mpx5700;
    char buffer[16];
    int8_t *ptr = &buffer;

    f1031v  = sample_f1031v();
    mpx5700 = sample_mpx5700();

    /* Cursor return. */
    send_command_lcd(0x80);
    _delay_ms(2);

    /* Report flows from F1031V sensor. */
    itoa(f1031v, buffer, 10);
    forward_bit_address(ptr);

    memcpy(buffer, " L/min (STP)", 16);
    forward_bit_address(ptr);

    /* Next line. */
    send_command_lcd(0xC0);

    /* Report pressures from MPX5700 sensor. */
    itoa(mpx5700, buffer, 10);
    forward_bit_address(ptr);

    memcpy(buffer, " cmH2O", 16);
    forward_bit_address(ptr);
}