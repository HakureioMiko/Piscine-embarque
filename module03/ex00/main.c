#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main()
{
    DDRD |= (1 << PD3);
    DDRD |= (1 << PD5);
    DDRD |= (1 << PD6);
    
    while (1)
    {
        PORTD |= (1 << PD5);
        _delay_ms(1000);
        PORTD &= ~(1 << PD5);
        PORTD |= (1 << PD6);
        _delay_ms(1000);
        PORTD &= ~(1 << PD6);
        PORTD |= (1 << PD3);
        _delay_ms(1000);
        PORTD &= ~(1 << PD3);
    }
    return (0);
}