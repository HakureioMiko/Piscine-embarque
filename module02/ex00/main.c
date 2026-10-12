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
    UCSR0A |= (1 << U2X0);

    // Configurer le débit à environ 115200 bauds
    UBRR0 = F_CPU / (8 x BAUD) - 1;

    // Configurer le format : 8 bits, aucune parité, 1 bit de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // Activer l'émetteur USART0
    UCSR0B = (1 << TXEN0);

    // UCSR0A = (1 << U2X0);
    // UBRR0 = F_CPU / (8 x BAUD) - 1;
    // UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // UCSR0B = (1 << TXEN0);
}

void uart_tx(char c)
{
    // Attendre que le registre de données soit disponible
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    // Placer le caractère dans le registre de transmission
    UDR0 = c;
}

int main(void)
{
    // Initialiser l'USART
    uart_init();

    // Envoyer Z toutes les secondes
    while (1)
    {
        uart_tx('Z');
        _delay_ms(1000);
    }

    return 0;
}
