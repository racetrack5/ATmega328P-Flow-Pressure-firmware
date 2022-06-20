#include "main.h"

/* Slope and intercepts for linear equation. */
#define F1031V_SLOPE 36.463 
#define F1031V_INTERCEPT 18.036

static void report_flow(uint16_t x, uint16_t y)
{
    /* Clear LCD and pass pointer. */
    char buffer[16];
    int8_t *ptr = &buffer;

    send_command_lcd(0x01);

    itoa(y, buffer, 10);
    forward_bit_address(ptr);

    memcpy(buffer, " L/min (STP)", 16);
    forward_bit_address(ptr);
}

void sample_f1031v()
{
    /* Retrieve data from ADC, convert to a voltage, and
     * solve for y. Send the data to the LCD.
     */
    uint16_t F1031V_x;
    uint16_t F1031V_y;
        
    F1031V_x = ADC;
    F1031V_x = F1031V_x / 1023 * 5;
    F1031V_y = (F1031V_SLOPE*F1031V_x)-F1031V_INTERCEPT; 

    report_flow(F1031V_x, F1031V_y);
}
