#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define UART_BAUD 115200

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    UDR0 = c;
}

void uart_printstr(const char *str)
{
    int i = 0;
    while (str[i])
    {
        uart_tx(str[i]);
        i++;
    }
    uart_tx('\n');
    uart_tx('\r');
}

void timer_ctc()
{
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    // 1024 prescaler otherwhie timer to short for 2s

    SREG = (1 << SREG_I);
    // page 20 7.3.1

    TIMSK1 = (1 << OCIE1A);
    // page 20 16.11.8

    const uint16_t time = (F_CPU / (1024 * 0.5) - 1);

    OCR1A = time;
}

void uart_init(void)
{
    // Activer le mode double vitesse
    UCSR0A |= (1 << U2X0);
    
    // Configurer le débit à environ 115200 bauds
    UBRR0 = F_CPU / (8 * UART_BAUD) - 1;
    // UCSR0A = F_CPU / UART_BAUD / 16 (autre facon de calculer);
    // Page 166 19.3.1

    // Configurer le format : 8 bits, aucune parité, 1 bit de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // Page 276 30. | 19.10.4

    // Activer l'émetteur USART0
    UCSR0B = (1 << TXEN0);  
    // 19.5
}

SIGNAL (TIMER1_COMPA_vect) { uart_printstr("Hello World!");}

int main()
{

    timer_ctc();
    uart_init();

    // while (1)
    // {
    //     uart_printstr("Hello world");
    //     _delay_ms(1000);
    // }
    while(1);
}