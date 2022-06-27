#include "main.h"

int main(void)
{
    /* Initialise LCD, ADC, and I2C bus. */
    init_lcd();

    init_adc();
    
    init_i2c();
    send_start_i2c();
    send_slaveaddr_i2c();

    sei();

    for( ; ;)
    {
        report_data();
        _delay_ms(50);
    }
}