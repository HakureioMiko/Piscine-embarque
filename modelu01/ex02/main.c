#include <avr/io.h>

int main()
{
    // DDRB |= (1 << PB1);

    // TCCR1A = (1 << COM1A0) | (1 << WGM11) | (1 << WGM10);
    // TCCR1B = (1 << WGM13) | (1 << CS12);
    // ICR1 = 31250;
    // OCR1A = (uint32_t)ICR1 * 10 / 100;

    DDRB |= (1 << PB1);

    TCCR1A = (1 << COM1A0) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12)| (1 << CS12);
    ICR1 = 31250;
    OCR1A = (uint32_t)ICR1 * 10 / 100;

    while (1){}
}
