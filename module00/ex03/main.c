#include <avr/io.h>
#include <util/delay.h>

int main()
{
    int checker = 0;

    DDRB |= (1 << PB0);
    DDRB &=~ (1 << PD2);

    while(1)
    {
        if (!(PIND & (1 << PD2)))
        {
            if (checker == 0)
            {
                checker = 1;
                PORTB |= (1 << PB0);
            }
            else
            {
                checker = 0;
                PORTB &=~ (1 << PB0);
                TCCR1B |= (1 << CS11) | (1 << CS10);
            }
            _delay_ms(250);
        }
    }
}