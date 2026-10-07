#include <avr/io.h>
#include <util/delay.h>

int main()
{
    // valeur de decrementation et d'incrementation
    int value = 0;
    // Sortie des DDR pour les LED
    DDRB |= (1 << PB0);
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB2);
    DDRB |= (1 << PB4);
    // Ouverture en entree pour les switch
    DDRB &=~ (1 << PD2);
    DDRB &=~ (1 << PD4);

    while (1)
    {
        // conditions le cas ou l'utilisateur appuis switch 1 pour incrementer
        if (!(PIND & (1 << PD2)))
        {
            if (value < 15)
                value++;
            _delay_ms(200);
        }
        // conditions le cas ou l'utilisateur appuis switch 2 pour decrementer
        if (!(PIND & (1 << PD4)))
        {
            if (0 < value)
                value--;
            _delay_ms(200);
        }
        // pour que l'utilisateur ne puisse pas maintenir le bouton
        while (!(PIND & (1 << PD2)))
            _delay_ms(1);
        while (!(PIND & (1 << PD4)))
            _delay_ms(1);

        // un tableau d'array pour savoir si les bits sont allumer ou eteins
        int array[4] = {0, 0, 0, 0};

        // Comparaison binaire
        // 8 = 1|0|0|0
        if (8 & value)
            array[0] = 1;

        // 4 = 0|1|0|0
        if (4 & value)
            array[1] = 1;

        // 2 = 0|0|1|0
        if (2 & value)
            array[2] = 1;

        // 1 = 0|0|0|1
        if (1 & value)
            array[3] = 1;

        // Conditions chercker de l'array
        if (array[0] == 1)
            PORTB |= (1 << PB4);
        else
            PORTB &=~ (1 << PB4);

        if (array[1] == 1)
            PORTB |= (1 << PB2);
        else
            PORTB &=~ (1 << PB2);
        
            if (array[2] == 1)
            PORTB |= (1 << PB1);
        else
            PORTB &=~ (1 << PB1);

        if (array[3] == 1)
            PORTB |= (1 << PB0);
        else
            PORTB &=~ (1 << PB0);
    }
}