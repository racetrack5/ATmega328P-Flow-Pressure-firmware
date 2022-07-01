#include "main.h"

/* Slope and intercepts for linear equation. */
#define MPX5700_M 0.0012858 
#define MPX5700_INTERCEPT 0.04
#define CONVERSION 10.1972

static volatile int16_t MPX5700_x; /* ISR to update this. */

ISR(TWI_vect)
{
    /* Receive byte of data sent over I2C bus. */
    MPX5700_x = TWDR;

    TWCR |= (1 << TWINT)|(1 << TWEA)|(1 << TWEN);
}

uint16_t sample_mpx5700(void)
{
    /* Convert data to a voltage and solve for y. */
    uint16_t MPX5700_y;

    MPX5700_x = MPX5700_x / 1023 * 5;
    MPX5700_y = (MPX5700_M*MPX5700_x)+MPX5700_INTERCEPT; 

    /* Convert to cmH2O. */
    MPX5700_y *= CONVERSION;

    return MPX5700_y;
}