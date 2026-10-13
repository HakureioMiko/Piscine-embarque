#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define UART_BAUD 115200

// Page 186 pour l'exemple de transmision
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
        // equivalent de putstr
        i++;
    }
    uart_tx('\n');
    uart_tx('\r');
}

void timer_ctc()
{
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    // 1024 prescaler car 256 trop grand pour 2s

    SREG = (1 << SREG_I);
    // active les interruption
    // page 20 7.3.1

    TIMSK1 = (1 << OCIE1A);
    // page 145 16.11.8
    // Bit 1

    OCR1A = (F_CPU / (1024 * 0.5) - 1);
    // calcul F_CPU / (1024 * 1) - 1 = 1s donc 0.5 pour double le temps donc 2s
}

// Page 185 exemple d'init
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

    // Activer l'emetteur USART0
    UCSR0B = (1 << TXEN0);
    // PAGE 201 20.11.3
    // enable TRANSMITTER
}

SIGNAL (TIMER1_COMPA_vect) 
{ 
    uart_printstr("Hello World!");
}
// page 66 12-1 interruptor vector 

int main()
{
    timer_ctc();
    // Timer sans boucle while avec interruption qui repete a chaque top de OCR1A toute les 2s
    uart_init();
    while(1);
}
