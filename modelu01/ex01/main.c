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
    // WGM12 page 141 == CTC CLEAR TIMER COMPARE qui commence a 0 puis monte a la valeur de OCR1A et va au max qui equivaut a 65000
    // CS12 page 142

    OCR1A = 31249;
    // on prend la moitie de 65000 - 1 parce que le timer commence a 0
    // OUTPUT COMPARE REGISTER page 121

    while(1){}
}