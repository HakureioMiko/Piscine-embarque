#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


SIGNAL (PCINT0_vect)
{
    
}

int main()
{
    SREG = (1 << SREG_I);
    // active les interruption
    // page 20 7.3.1

}