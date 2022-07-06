#include "main.h"

int main(void)
{
    init_lcd();
    init_usart(9600);
    init_adc();
    init_i2c();
    init_timer();

    sei();

    uint8_t input;

    while(1)
    {
        if (return_overflows() == 6)
        {
            report_data();
            zero_overflows();
        }

        switch(return_i2c_status())
        {
            case 0:
                if (TWCR & (1 << TWINT))
                    send_slaveaddr_i2c();
                break;
            case 1:
                if (TWCR & (1 << TWINT))
                    send_start_i2c();
                break;
            case 2:
                if (TWCR & (1 << TWINT))
                    send_slaveaddr_i2c();
                break;
        }

        if (isrchk_usart())
            input = return_usart;
    }
}