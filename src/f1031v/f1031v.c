#include "main.h"

/* Slope and intercepts for linear equation. */
#define F1031V_M 36.463 
#define F1031V_INTERCEPT -18.036

static volatile uint16_t F1031V_x; /* ISR to update this. */ 

ISR(ADC_vect)
{
    /* Interrupt when ADC conversion is complete. */
    F1031V_x = ADC;

    /* Start conversion again. */
    ADCSRA |= (1 << ADSC);
}

uint16_t sample_f1031v()
{
    /* Convert ADC output to a voltage and solve for y. */
    uint16_t F1031V_y;
        
    F1031V_x = F1031V_x / 1023 * 5;
    F1031V_y = (F1031V_M*F1031V_x)+F1031V_INTERCEPT; 

    return F1031V_y;
}
