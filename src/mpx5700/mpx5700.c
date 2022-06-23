#include "main.h"

/* Slope and intercepts for linear equation. */
#define MPX5700_M 0.0012858 
#define MPX5700_INTERCEPT 0.04

static volatile int8_t MPX5700_x; /* ISR to update this. */

ISR(TWI_vect)
{
    /* Receive bytes from MPX5700 over I2C bus. */
    MPX5700_x = receive_data_i2c();
}

uint8_t sample_mpx5700()
{
    /* Convert data to a voltage and solve for y. */
    uint8_t MPX5700_y;

    MPX5700_x = MPX5700_x / 255 * 5;
    MPX5700_y = (MPX5700_M*MPX5700_x)+MPX5700_INTERCEPT; 

    return MPX5700_y;
}