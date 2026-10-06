#include <avr/io.h>
#include <util/delay.h>

int main()
{
    int value = 0;
    DDRB |= (1 << PB0);
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB2);
    DDRB |= (1 << PB4);
    DDRB &=~ (1 << PD2);
    DDRB &=~ (1 << PD4);

    while (1)
    {
        if (!(PIND & (1 << PD2)))
        {
            if (value < 15)
                value++;
            _delay_ms(200);
        }
        if (!(PIND & (1 << PD4)))
        {
            if (0 < value)
                value--;
            _delay_ms(200);
        }
        int valueCopy = value;

        int array[4] = {0, 0, 0, 0};

        if (8 & value)
            array[0] = 1;

        if (4 & value)
            array[1] = 1;

        if (2 & value)
            array[2] = 1;

        if (1 & value)
            array[3] = 1;

        if (array[0] == 1)
            PORTB |= (1 << PB4);
        else
            PORTB &=~ (1 << PB4);

        if (array[1] == 1)
            PORTB |= (1 << PB2);
        else
            PORTB &=~ (1 << PB2);
        
            if (array[2] == 1)
            PORTB |= (1 << PB1);
        else
            PORTB &=~ (1 << PB1);

        if (array[3] == 1)
            PORTB |= (1 << PB0);
        else
            PORTB &=~ (1 << PB0);
    }
}