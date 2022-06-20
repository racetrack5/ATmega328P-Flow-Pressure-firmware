#include "main.h"

void poll_adc()
{
    /* Polling rather than IQRs for now. */
    if (ADCSRA &= ~(1 << ADSC))
        sample_f1031v();
}

void init_adc()
{
    /* Set pin modes and init ADC. Reference voltage is AVCC (5V), 
     * ADC operating in 10-bit mode with pre-scalar at 128 (125KHz).
     */
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2);
    ADCSRA |= (1 << ADEN);
}