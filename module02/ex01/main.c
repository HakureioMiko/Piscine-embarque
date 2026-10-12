#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void uart_printstr(const char *str)
{

}

void timer_ctc()
{

}

void uart_init(void)
{
    // Activer le mode double vitesse
    UCSR0A |= (1 << U2X0);
    
    // Configurer le débit à environ 115200 bauds
    UBRR0 = F_CPU / (8 * UART_BAUD) - 1;
    // UCSR0A = F_CPU / UART_BAUD / 16;
    // Page 166 19.3.1

    // Configurer le format : 8 bits, aucune parité, 1 bit de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // Page 276 30. | 19.10.4

    // Activer l'émetteur USART0
    UCSR0B = (1 << TXEN0);  
    // 19.5
}

int main()
{

    timer_ctc();
    uart_init();

    while(1);
}