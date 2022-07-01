#include "main.h"

int main(void)
{
    init_lcd();
    init_usart(9600);

    init_adc();
    
    init_i2c();
    send_start_i2c();
    send_slaveaddr_i2c();

    sei();

    for ( ; ;)
    {
        report_data();

        //if (isrchk_usart())
        //    return_usart();

        _delay_ms(50);
    }
}