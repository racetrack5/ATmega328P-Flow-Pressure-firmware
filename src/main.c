#include "main.h"

void main()
{
    LCD_INIT();

    ADC_INIT();
    
    while(1)
    {
            F1031V();

            if (ADCSRA &= ~(1 << 6))
                ADCSRA |= (1 << 6);
                
            // Slow loop (optional)
            _delay_ms(100);
    }
}
