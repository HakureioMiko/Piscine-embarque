#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void blue()
{
    PORTD |= (1 << PD3);
}

void red()
{
    PORTD |= (1 << PD5);
}

void green()
{
    PORTD |= (1 << PD6);
}

void closeRGB()
{
    _delay_ms(1000);
    PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD5);
    PORTD &= ~(1 << PD3);
}

int main()
{
    DDRD |= (1 << PD3);    
    DDRD |= (1 << PD5);    
    DDRD |= (1 << PD6);
    
    while(1)
    {
        // red
        red();
        closeRGB();

        // green
        green();
        closeRGB();

        // blue
        blue();
        closeRGB();

        // yellow
        red();
        green();
        closeRGB();

        // cyan
        green();
        blue();
        closeRGB();

        // magenta
        red();
        blue();
        closeRGB();

        // white
        red();
        green();
        blue();
        closeRGB();
    }
}