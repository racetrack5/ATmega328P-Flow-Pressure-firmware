#include "main.h"

int main()
{
    /* Initialise LCD, ADC, and I2C bus. */
    init_lcd();

    init_adc();
    
    init_i2c();
    /* send_start_i2c();
     * send_slaveaddr_i2c(0);
     */

    while(1)
    {
        /* Poll ADC for F1031V reading and set bit to re-evaluate. */
        poll_adc();

        if (ADCSRA &= ~(1 << ADSC))
            ADCSRA |= (1 << ADSC);

        /* Optional delay */
        _delay_ms(100);
    }

    return 0;
}