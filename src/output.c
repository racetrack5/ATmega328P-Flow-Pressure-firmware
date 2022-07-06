#include "main.h"

#define FLOW " L/min (STP)"
#define FLOW_USART "\tL/min (STP)\t"
#define PRESSURE " cmH2O"
#define PRESSURE_USART "\tcmH2O\n"

static void report_data_usart(uint16_t f1031v, uint16_t mpx5700)
{
    char buffer[16];

    itoa(f1031v, buffer, 10);
    xmit_usart(&buffer);

    memcpy(buffer, FLOW_USART, 16);
    xmit_usart(&buffer);

    itoa(mpx5700, buffer, 10);
    xmit_usart(&buffer);

    memcpy(buffer, PRESSURE_USART, 16);
    xmit_usart(&buffer);
}

static void report_data_lcd(uint16_t f1031v, uint16_t mpx5700)
{
    char buffer[16];

    /* Blank LCD. */
    send_command_lcd(0x01);

    /* Report flows from F1031V sensor. */
    itoa(f1031v, buffer, 10);
    forward_bit_address(&buffer);

    memcpy(buffer, FLOW, 16);
    forward_bit_address(&buffer);

    /* Next line. */
    send_command_lcd(0xC0);

    /* Report pressures from MPX5700 sensor. */
    itoa(mpx5700, buffer, 10);
    forward_bit_address(&buffer);

    memcpy(buffer, PRESSURE, 16);
    forward_bit_address(&buffer);
}

void report_data(void)
{
    int16_t f1031v = sample_f1031v();
    int16_t mpx5700 = sample_mpx5700();

    report_data_lcd(f1031v, mpx5700);
    report_data_usart(f1031v, mpx5700);
}