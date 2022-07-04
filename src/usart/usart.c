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

void xmit_usart(int8_t *ptr)
{
    while(*ptr > 0)
    {
        UDR0 = *ptr;
        while(!(UCSR0A & (1 << UDRE0))) ; /* Wait for previous byte. */
        ptr++; /* Next byte to send. */
    }
}

void init_usart(uint16_t baud_rate)
{
    /* Enable Tx and Rx. */
    uint16_t baud_prescale = (F_CPU/16/baud_rate)-1;
    UBRR0L = (uint8_t)(baud_prescale & 0xFF);
    UBRR0H = (uint8_t)(baud_prescale >> 8);

    UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
} 