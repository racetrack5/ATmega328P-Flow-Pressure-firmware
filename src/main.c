#include "main.h"

int main()
{
    /* Initialise LCD, ADC, and I2C bus. */
    int16_t f1031v;
    int8_t mpx5700;

    char buffer[16];
    int8_t *ptr = &buffer;

    init_lcd();

    init_adc();
    
    init_i2c();
    send_start_i2c();
    send_slaveaddr_i2c(0);

    while(1)
    {
        f1031v = sample_f1031v();

        mpx5700 = sample_mpx5700();

        send_command_lcd(0x01);

        itoa(f1031v, buffer, 10);
        forward_bit_address(ptr);
        memcpy(buffer, " L/min (STP)", 16);
        forward_bit_address(ptr);

        send_command_lcd(0xC0);

        itoa(mpx5700, buffer, 10);
        forward_bit_address(ptr);
        memcpy(buffer, " cmH2O", 16);
        forward_bit_address(ptr);

        /* Optional delay */
        _delay_ms(1);
    }

    return 0;
}