#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define UART_BAUD 115200

// Page 189 pour l'exemple de receive
char uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0)))
    {
    }

    return (UDR0);
}

// Page 186 pour l'exemple de transmision
void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    UDR0 = c;
}


void uart_init(void)
{
    // Activer le mode double vitesse
    UCSR0A |= (1 << U2X0);
    
    // Configurer le débit a environ 115200 bauds
    UBRR0 = F_CPU / (8 * UART_BAUD) - 1;
    // UCSR0A = F_CPU / UART_BAUD / 16 (autre facon de calculer);
    // Page 182 20-1

    // Configurer le format : 8 bits, aucune parite, 1 bit de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // Page 276 30. | 19.10.4

    // Activer l'emetteur et receveur USART0
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    // PAGE 201 20.11.3
    // enable TRANSMITTER | RECEIVER
}

int main()
{
    char a;
    uart_init();
    // initialisation de l'uart

    while(1)
    {
        a = uart_rx();
        uart_tx(a);
    }
}