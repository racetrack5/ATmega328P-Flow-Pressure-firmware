#include <avr/interrupt.h>
#include "main.h"

int main()
{
    /* Initialise LCD, ADC, and I2C bus. */
    init_lcd();

    init_adc();
    
    init_i2c();
    send_start_i2c();
    send_slaveaddr_i2c(0);

    /* Enable interrupts. */
    sei();

    while(1)
    {
        report_data();

        /* Delay to avoid LCD corruption. */
        _delay_ms(20);
    }

    return 0;
}