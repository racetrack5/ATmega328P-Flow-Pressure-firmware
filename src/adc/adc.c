#include "main.h"

void ADC_INIT()
{
    // PORTC init
    DDRC = 0x00;
    PORTC = 0x00;

    // ADC high reference source is AVCC
    ADMUX |= (1 << 6);
    ADMUX &= ~(1 << 7);
    
    // 10-bit ADC 
    ADMUX &= ~(1 << 5);

    //Connect A0 to ADC
    ADMUX &= ~(1 << 0);
    ADMUX &= ~(1 << 1);
    ADMUX &= ~(1 << 2);
    ADMUX &= ~(1 << 3);
    ADMUX &= ~(1 << 4);
    
    // Prescalar divisor = 128
    ADCSRA |= (1 << 0);
    ADCSRA |= (1 << 1);
    ADCSRA |= (1 << 2);
    
    // Enable ADC
    ADCSRA |= (1 << 7);
}
