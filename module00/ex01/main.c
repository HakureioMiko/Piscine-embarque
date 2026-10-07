#include <avr/io.h>

int main (void)
{
    DDRB  |= (1 << PB0);
    // DDRx = DATA DIRECTION REGISTER : defini la direction de chaque broche du port
    // BIT = 1 -> La broche est une sortie
    // BIT = 0 -> La broche est une entree
    PORTB |= (1 << PB0);
    // PORTB = PORT DATA REGISTER
    // En sortie : écrit la valeur sur la broche (1 = HIGH/5V, 0 = LOW/0V)
    // En entrée : active (1) ou désactive (0) la résistance pull-up interne
}