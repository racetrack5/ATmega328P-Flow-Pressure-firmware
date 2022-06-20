#include "main.h"

int main()
{
    init_lcd();

    init_adc();
    
    while(1)
    {
        /* Check each sensor and re-evalute analog inputs. */
        poll_adc();

        if (ADCSRA &= ~(1 << ADSC))
            ADCSRA |= (1 << ADSC);
                
        /* Optional delay */
        _delay_ms(100);
    }

    return 0;
}