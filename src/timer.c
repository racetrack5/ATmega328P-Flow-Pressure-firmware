#include "main.h"

static volatile uint8_t overflows;

ISR(TIMER0_OVF_vect)
{
    overflows++;
}

uint8_t return_overflows(void)
{
    return overflows;
}

void zero_overflows(void)
{
    overflows = 0;
}

void init_timer(void)
{
    TCNT0 = 0x00;
    TCCR0B = (1 << CS00)|(1 << CS02);
    TIMSK0 = (1 << TOIE0);
}