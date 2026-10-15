#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_rgb(void)
{
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

    // timer for OC0A OC0B
    // page 113 15.9.1
    TCCR0A = (1 << COM0A1) |
             (1 << COM0B1) |
             (1 << WGM01)  |
             (1 << WGM00);

    // prescaler 64
    // page 116 15.9.2
    TCCR0B = (1 << CS01) | (1 << CS00);

    // timer for 0C2B
    // page 162 18.11.1
    TCCR2A = (1 << COM2B1) |
             (1 << WGM21)  |
             (1 << WGM20);

    // prescaler 64
    // page 165 18.11.2
    TCCR2B = (1 << CS22);

    OCR0A = 0; // Red
    OCR0B = 0; // Green;
    OCR2B = 0; // Blue;
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r;
    OCR0A = g;
    OCR2B = b;
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
