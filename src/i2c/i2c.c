#include "main.h"

/* Documented I2C slave address of MPX5700. */
#define SLAVE_ADDRESS 0x16

/* Relevant transmit and receiver codes. */
#define XMIT_START 0x08
#define XMIT_ADDR_W_ACK 0x18
#define XMIT_DATA_W_ACK 0x28
#define XMIT_ADDR_R_ACK 0x40
#define XMIT_DATA_R_ACK 0x50

void send_stop_i2c()
{
    TWCR |= (1 << TWINT)|(1 << TWSTO)|(1 << TWEN);
}

uint8_t receive_data_i2c()
{
    /* Acknowledge (ACK) receipt of data. */
    TWCR |= (1 << TWINT)|(1 << TWEA)|(1 << TWEN);

    return TWDR;
}

void send_data_i2c(uint8_t *byte)
{
    /* Pass data to slave device. */
    TWDR = *byte;
    TWCR |= (1 << TWINT)|(1 << TWEN);
}

void send_slaveaddr_i2c()
{
    /* Send slave address to slave device. Master 1=write, 0=read. */
    TWDR = SLAVE_ADDRESS;
    TWCR |= (1 << TWINT)|(1 << TWEN);
}

void send_start_i2c()
{
    /* Send Start and return byte stored within TWSR. */
    TWCR |= (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
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