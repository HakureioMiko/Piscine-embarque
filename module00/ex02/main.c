#include <avr/io.h>

int main()
{
    DDRB |= (1 << PB0);     // PB0 (ICP1) en sortie → LED
    DDRB &=~ (1 << PD2);    // PD2 (INTO) en entrée → Bouton

    while (1) {
        if (!(PIND & (1 << PD2))) {    // Bouton pressé (LOW)
            PORTB |= (1 << PB0);        // LED ON
        } else {
            PORTB &= ~(1 << PB0);       // LED OFF
        }
    }
}