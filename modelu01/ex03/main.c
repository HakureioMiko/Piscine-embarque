#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB |= (1 << PB1);

    TCCR1A = (1 << COM1A0) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12);
    ICR1 = 31250;
    int value = 10;
    OCR1A = (uint32_t)ICR1 * value / 100;

    DDRD &= ~(1 << PD2);
    DDRD &= ~(1 << PD4);
    PORTD |= (1 << PD2);

    while (1)
    {
        if (!(PIND & (1 << PD2)))
        {
            _delay_ms(20);
            if (value < 100)
            {
                value += 10;
            OCR1A = (uint32_t)ICR1 * value / 100;
            }
            while (!(PIND & (1 << PD2))); 
        }

        if (!(PIND & (1 << PD4)))
        {
            _delay_ms(20);
            if (10 < value)
            {
                value -= 10;
                OCR1A = (uint32_t)ICR1 * value / 100;
            }
            while (!(PIND & (1 << PD4)));
        }
    }
}
