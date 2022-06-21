#include "main.h"

void poll_i2c()
{
    /* Receive bytes from MPX5700 over I2C bus. */
    receive_data_i2c(0);
}