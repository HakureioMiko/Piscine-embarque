#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_rgb()
{
    // Rouge : PD5 = OC0B
    // Vert  : PD3 = OC2B
    // Bleu  : PB3 = OC2A
    DDRD |= (1 << DDD5) | (1 << DDD3);
    DDRB |= (1 << DDB3);

    TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    // page 14.7.3
    
    // Prescaler Timer0 = 64
    TCCR0B = (1 << CS01) | (1 << CS00);

    // Timer2 : Fast PWM 8 bits, sorties OC2A et OC2B
    TCCR2A = (1 << COM2A1) |
             (1 << COM2B1) |
             (1 << WGM21) |
             (1 << WGM20);

    // Prescaler Timer2 = 64
    TCCR2B = (1 << CS22);

    // LED eteinte au depart
    OCR0B = 0;
    
    OCR2B = 0;
    OCR2A = 0;
    // page 17.11.5
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r;
    OCR2B = g;
    OCR2A = b;
}

void wheel(uint8_t pos)
{
    pos = 255 - pos;
    if (pos < 85)
    {
        set_rgb(255 - pos * 3, 0, pos * 3);
    }
    else if (pos < 170)
    {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    }
    else
    {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}

int main()
{
    init_rgb();

    while (1)
    {
        for (uint16_t i = 0; i < 256; i++)
        {
            wheel((uint8_t)i);
            _delay_ms(10);
        }
    }
}
