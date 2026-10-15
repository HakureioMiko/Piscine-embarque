#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define UART_BAUD 115200

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
    // enable TRANSFER | RECEIVER
}

void init_rgb(void)
{
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

    // timer for OC0A OC0B
    // page 113 15.9.1
    TCCR0A = (1 << COM0A1) |
             (1 << COM0B1) |
             (1 << WGM01)  |
             (1 << WGM00);

    // prescaler 64
    // page 116 15.9.2
    TCCR0B = (1 << CS01) | (1 << CS00);

    // timer for 0C2B
    // page 162 18.11.1
    TCCR2A = (1 << COM2B1) |
             (1 << WGM21)  |
             (1 << WGM20);

    // prescaler 64
    // page 165 18.11.2
    TCCR2B = (1 << CS22);

    OCR0A = 0; // Red
    OCR0B = 0; // Green;
    OCR2B = 0; // Blue;
}

char uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0)))
    {
    }

    return (UDR0);
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    UDR0 = c;
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r;
    OCR0A = g;
    OCR2B = b;
}

uint8_t convert_hex(char c)
{
    // hexadecimal convert;
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    
    return -1;
}

uint8_t hex_value(char first, char second)
{
    uint8_t left = convert_hex(first);
    uint8_t right = convert_hex(second);

    if (left < 0 || right < 0)
        return -1;

    // RGB color > 16 * First + Second
    // 16 x 15 = 240 + 15 = 255
    return (16 * left + right);
}


int main()
{
    uart_init();
    init_rgb();

    char line[7];
    // #RRGGBB
    int i = 0;
    
    while (1)
    {
        char rx_c = uart_rx();
        uart_tx(rx_c);

        // to receive and transfer;
        if (rx_c == '\n' || rx_c == '\r')
        {
            if (i == 7 && line[0] == '#')
            {
                // get rgb value;
                uint8_t r = hex_value(line[1], line[2]);
                uint8_t g = hex_value(line[3], line[4]);
                uint8_t b = hex_value(line[5], line[6]);

                // check if not error
                if (r >= 0 && g >= 0 && b >= 0)
                    set_rgb(r, g, b);
            }
            // reset
            i = 0;
        }
        else if(i < 7)  
        {
            line[i] = rx_c;
            i++;
        }
        else
        {
            i = 0;
        }
    }
}