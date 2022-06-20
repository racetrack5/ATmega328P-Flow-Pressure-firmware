#include "main.h"

/* SCL = PC5
 * SDA = PC4 */

void I2C_STOP()
{
    // SCL and SCA high
    PORTC |= (1 << 5);
    PORTC |= (1 << 4);

    // Init TWI
    TWCR |= (1 << 7); // TWI Interrupt Flag
    TWCR |= (1 << 5); // Set Master
    TWCR |= (1 << 2); // Enable interface

    _delay_ms(1000);

    // SDA high to trigger Stop
    PORTC |= (1 << 4);
}

void I2C_STRT()
{
    // SCL and SCA high
    PORTC |= (1 << 5);
    PORTC |= (1 << 4);

    _delay_ms(1000);

    // SDA low to trigger Start
    PORTC &= ~(1 << 4);
}

void I2C_INIT() // Prepare for Start condition
{
    // Configure PORTC
    DDRC |= (1 << 5);
    DDRC |= (1 << 4);

    _delay_ms(1000);
}
