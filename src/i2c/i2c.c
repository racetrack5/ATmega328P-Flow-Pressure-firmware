#include "main.h"

/* Documented I2C slave address of MPX5700. */
#define SLAVE_ADDRESS 0x16

uint8_t receive_data_i2c()
{
    /* Acknowledge (ACK) receipt of data. */
    TWCR |= (1 << TWINT)|(1 << TWEA)|(1 << TWEN);

    return TWDR;
}

void send_slaveaddr_i2c()
{
    /* Send slave address to slave device. */
    TWDR = SLAVE_ADDRESS;
    TWCR |= (1 << TWINT)|(1 << TWEN);
}

void send_start_i2c()
{
    /* Send Start signal to slave device. */
    TWCR |= (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
}

void init_i2c()
{
    /* I2C using two-wire interface. Operating @ 100KHz (32 bit rate, 
     * no pre-scalar). CPU_clock/(16 + 2*TWBR*(4^prescaler)) */
    TWBR = 0x20;
    TWCR |= (1 << TWEN);
    TWCR |= (1 << TWIE);
}