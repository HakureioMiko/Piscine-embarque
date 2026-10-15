#include <avr/io.h>

void __vector_1(void) __attribute__((signal));

void __vector_1(void)
{
    PORTB ^= (1 << PB0);
    _delay_ms(20);
}

int main()
{
    DDRB |= (1 << PB0);
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    EICRA = (1 << ISC01);
    EIMSK = (1 << INT0);

    SREG = (1 << SREG_I);

    while (1)
    {
    }

}