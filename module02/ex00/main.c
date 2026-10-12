#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define BAUD 115200

#include <avr/io.h>
#include <util/delay.h>

void uart_init(void)
{
    // Activer le mode double vitesse
    // UCSR0A |= (1 << U2X0);

    // Configurer le débit à environ 115200 bauds
    UBRR0 = F_CPU / (2 * BAUD) - 1;
    // Page 166 20.3

    // Configurer le format : 8 bits, aucune parité, 1 bit de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // Page 276 30. | 19.10.4

    // Activer l'émetteur USART0
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);  
    // 19.19.3
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = c;
}

int main(void)
{
    uart_init();

    while (1)
    {
        uart_tx('Z');
        _delay_ms(1000);
    }

    return 0;
}
