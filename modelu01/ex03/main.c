#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB |= (1 << PB1);

    // meme etape que l'exercice d'avant sauf qu'on a une value qui predefini a 50%
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12);
    ICR1 = 65000;
    int value = 50;
    OCR1A = ((uint32_t)ICR1 * value) / 100;

    // ouverture des switch
    DDRD &= ~(1 << PD2);
    DDRD &= ~(1 << PD4);
    PORTD |= (1 << PD2);
    PORTD |= (1 << PD4);

    while (1)
    {
        if (!(PIND & (1 << PD2)))
        {
            _delay_ms(20);
            if (value < 100)
            {
                // incrementer le rapport cyclique
                value += 10;
                OCR1A = ((uint32_t)ICR1 * value) / 100;
            }
            while (!(PIND & (1 << PD2))); 
        }

        if (!(PIND & (1 << PD4)))
        {
            _delay_ms(20);
            if (10 < value)
            {
                // decrementer le rapport cyclique  
                value -= 10;
                OCR1A = ((uint32_t)ICR1 * value) / 100;
            }
            while (!(PIND & (1 << PD4)));
        }
    }
}
