#include "main.h"

/* Documented I2C slave address of MPX5700. */
#define SLAVE_ADDRESS 0x16

/* Reply codes. */
#define XMIT_START 0x08
#define XMIT_ADDRESS_ACK 0x18
#define XMIT_DATA_ACK 0x28

uint8_t send_data_i2c(uint8_t *byte)
{
    /* Pass data to slave device. */
    TWCR |= (1 << TWINT)|(1 << TWEN);
    TWDR = *byte;

    wait_i2c();

    return reply_i2c(XMIT_DATA_ACK);
}

uint8_t send_slaveaddr_i2c()
{
    /* Send slave address to slave device. */
    TWCR |= (1 << TWINT)|(1 << TWEN);
    TWDR = SLAVE_ADDRESS;

    wait_i2c();

    return reply_i2c(XMIT_ADDRESS_ACK);
}

uint8_t send_start_i2c()
{
    /* Send Start and return byte stored within TWSR. */
    TWCR |= (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);

    wait_i2c();

    return reply_i2c(XMIT_START);
}

uint8_t reply_i2c(uint8_t xmit)
{
    /* Check status register. */
    if (TWSR == xmit)
        return 1;
    else
        return 0;
}

void wait_i2c()
{
    while (TWCR &= ~(1 << TWINT)) ;
}

void init_i2c()
{
    /* I2C using two-wire interface. Operating @ 100KHz (32 bit rate, 
     * no pre-scalar). CPU_clock/(16 + 2*TWBR*(4^prescaler)) */
    TWBR = 0x20;
    TWCR |= (1 << TWEN);
}