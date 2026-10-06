#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB &=~ (1 << PD2);
    DDRB &=~ (1 << PD4);

    while (1)
    {
        if (!(PIND & (1 << PD2)))
        {

        }
        if (!(PIND & (1 << PD4)))
        {
            PORTB |= (1 << PB0);
        }
    }
}