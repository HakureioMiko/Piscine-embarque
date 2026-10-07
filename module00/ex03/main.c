#include <avr/io.h>
#include <util/delay.h>

int main()
{
    int checker = 0;

    DDRB |= (1 << PB0); // PB0 (ICP1) en sortie → LED
    DDRD &=~ (1 << PD2); // PD2 (INTO) en entrée → Bouton

    // pull up resistance
    PORTD |= (1 << PD2);

    while(1)
    {
        // PINx = PORT INPUT REGISTER
        // Lit l'état logique actuel de chaque broche du port, quelle que soit sa direction
        // Du coup elle detecte si l'utilisateur change l'etat du switch PD2 en appuyant dessus
        if (!(PIND & (1 << PD2)))
        {
            _delay_ms(20);


            // ^= comparaison binaire inverse
            if (!checker)
                PORTB ^= (1 << PB0);
            checker = 1;
            // _delay_ms permet de faire attendre le processus en miliseconds
            // cette boucle permet le cas ou l'utilisateur maintiens le bouton PD2
            // pour ne pas avoir un cercle vicieux d'allumer eteint.
            while (!(PIND & (1 << PD2)))
                _delay_ms(1);
        }
        else
            checker = 0;
    }
}