#include <avr/io.h>
#include <util/delay.h>

int main()
{
    int checker = 0;
    int pressed = 0;

    DDRB |= (1 << PB0); // PB0 (ICP1) en sortie → LED
    DDRB &=~ (1 << PD2); // PD2 (INTO) en entrée → Bouton

    while(1)
    {
        // PINx = PORT INPUT REGISTER
        // Lit l'état logique actuel de chaque broche du port, quelle que soit sa direction
        // Du coup elle detecte si l'utilisateur change l'etat du switch PD2 en appuyant dessus
        if (!(PIND & (1 << PD2)))
        {
            if (checker == 0)
            {
                pressed = 1;
                checker = 1;
                PORTB |= (1 << PB0);
            }
            else
            {
                checker = 0;
                PORTB &=~ (1 << PB0);
            }
            // _delay_ms permet de faire attendre le processus en miliseconds
            _delay_ms(150);
            // cette boucle permet le cas ou l'utilisateur maintiens le bouton PD2
            // pour ne pas avoir un cercle vicieux d'allumer eteint.
            while (!(PIND & (1 << PD2)))
                _delay_ms(1);
        }
    }
}