#include "main.h"

static volatile uint8_t usart_byte;
static volatile uint8_t usart_flag;

ISR(USART_RX_vect)
{
    /* ISR driven USART Rx. */
    usart_byte = UDR0;
    usart_flag = 1;
}

uint8_t isrchk_usart(void)
{
    return usart_flag;
}

uint8_t return_usart(void)
{
    usart_flag = 0;
    return usart_byte;
}

void xmit_usart(uint8_t byte)
{
    /* Tx one byte of data. */
    UDR0 = byte;
}

void init_usart(uint16_t baud_rate)
{
    /* Enable Tx and Rx. */
    uint16_t baud_prescale = F_CPU/(baud_rate*16)-1;
    UBRR0L = (uint8_t)(baud_prescale & 0xFF);
    UBRR0H = (uint8_t)(baud_prescale >> 8);

    UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
} 