#include <avr/io.h>

int main()
{
    DDRB |= (1 << PB1);

    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CLKPS0);
    OCR1A = 32768;


    while (1){}
}