#include <avr/io.h>

int main()
{
    DDRB |= (1 << (PB1));

    while (1)
    {
        PORTB ^= (1 << (PB1));
        __builtin_avr_delay_cycles(8000000);
        // builtin pour faire un temps en ticks ce qui permet d'alterner 0.5 car l'avr et de 16mhz
    }
}