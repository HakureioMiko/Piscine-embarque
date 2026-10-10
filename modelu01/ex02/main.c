#include <avr/io.h>

int main()
{
    DDRB |= (1 << PB1);

    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12)| (1 << CS12);
    // mode 14 PWM Pour faire le rapport cyclique
    ICR1 = 65000;
    // temps calculer par le prescaler 256/16000000 = 0.0000.... | 1/0.000016 | 65000 == 1s
    OCR1A = ((uint32_t)ICR1 * 10) / 100;
    // avec le calcul ici on prend 10% du coup normalment 0.1 allumer 0.9s eteint
    // page 137 calcul OCRPWD

    while (1){}
}
