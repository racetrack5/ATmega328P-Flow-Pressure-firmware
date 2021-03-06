#include "main.h"

/* Documented I2C slave address of MPX5700. */
#define SLAVE_ADDRESS 0x16

static volatile uint8_t i2c_status;

void increment_i2c_status(void)
{
    i2c_status++;
}

uint8_t return_i2c_status(void)
{
    return i2c_status;
}

void send_slaveaddr_i2c(void)
{
    /* Send slave address to slave device. */
    TWDR = SLAVE_ADDRESS;
    TWCR |= (1 << TWINT)|(1 << TWEN);
}

void send_start_i2c(void)
{
    /* Send Start signal to slave device. */
    TWCR |= (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
}

void init_i2c(void)
{
    /* I2C using two-wire interface. Operating @ 100KHz (32 bit rate, 
     * no pre-scalar). CPU_clock/(16 + 2*TWBR*(4^prescaler)) */
    TWBR = 0x20; //0x0c for 400KHz
    TWSR = 0x00;
    TWCR |= (1 << TWEN)|(1 << TWIE);
}