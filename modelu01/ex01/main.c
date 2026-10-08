// bonne chance, c'etait incomprehensible

#include <avr/io.h>

int main()
{
    DDRB |= (1 << PB1);
    // PB1 OC1A (Timer/Counter1 Output Compare Match A Output) page 91
    TCCR1A = (1 << COM1A0); // page 140
    TCCR1B = (1 << WGM12) | (1 << CS12);
    // calcul binaire de WGM 
    // ^ WGM13 WGM12 WGM11 WGM10
    // WGM12 page 141 == CTC CLEAR TIMER COMPARE qui commence a 0 puis monte a la valeur de OCR1A IRC1
    // CS12 page 142

    OCR1A = 32768;
    // OUTPUT COMPARE REGISTER page 121

    while(1){}
}




















// int main(void)
// {
//     // PB1 (OC1A) en sortie
//     // c'est 1 broche physique avec 2 fonctions:
//     // PB1 (LED) OC1A comparaison avec timer1
//     DDRB |= (1 << PB1);

//     // bascule (toggle) la sortie OC1A à chaque comparaison.
//     TCCR1A = (1 << COM1A0);

//     // WGM12 = mode CTC
//     // CS12 = prescaler 256
//     TCCR1B = (1 << WGM12) | (1 << CS12);

//     // F_CPU = 16 MHz
//     // F_Timer = 16 MHz / 256 = 62500 Hz
//     //
//     // Toggle toutes les 500 ms :
//     // OCR1A = 500 ms / 16 us - 1
//     //       = 31249

//     OCR1A = 31249; // la valeur de comparaison

//     while (1)
//     {
//     }
// }
