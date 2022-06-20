#include "main.h"

int main(void)
{
    init_lcd();

    init_adc();
    
    while(1)
    {
        /* Check each sensor and re-evalute
         * analog inputs if required. */
        poll_adc();

        if (ADCSRA &= ~(1 << 6))
            ADCSRA |= (1 << 6);
                
        /* Optional delay */
        _delay_ms(100);
    }

    return 0;
}