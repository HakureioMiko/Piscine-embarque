#include <avr/io.h>

int main()
{
    DDRB |= (1 << (PB1));

    while (1)
    {
        PORTB ^= (1 << (PB1));
        __builtin_avr_delay_cycles(8000000);
    }
}