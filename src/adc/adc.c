#include "main.h"

void poll_adc()
{
    /* Polling rather than IQRs. */
    if (ADCSRA &= ~(1 << 6))
        sample_f1031v();
}

void init_adc()
{
    /* Set pin modes and init ADC. Reference
     * voltage is AVCC (connected to 5V), and the
     * ADC will operate in 10-bit mode with
     * pre-scalar set to 128 (125K samples).
     */
    DDRC = 0x00;
    PORTC = 0x00;

    ADMUX |= (1 << 6);
    ADMUX &= ~(1 << 7);
    
    ADMUX &= ~(1 << 5);

    ADMUX &= ~(1 << 0);
    ADMUX &= ~(1 << 1);
    ADMUX &= ~(1 << 2);
    ADMUX &= ~(1 << 3);
    ADMUX &= ~(1 << 4);
    
    ADCSRA |= (1 << 0);
    ADCSRA |= (1 << 1);
    ADCSRA |= (1 << 2);
    
    ADCSRA |= (1 << 7);
}