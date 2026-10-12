#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Baud = Speed transmission
#define UART_BAUD 115200UL

// Asynchronous Normal mode => (U2Xn = 0)

// Send one character to the UART
void uart_tx(char data)
{
	// Wait for the transmit buffer to be empty
	// If the UDRE0 bit in the UCSR0A register is set,
	// it means the transmit buffer is empty and ready to receive new data.
	while ( !( UCSR0A & (1 << UDRE0)) );

	// Load the data into the UDR0 register to send it
	// The UDR0 register is the data register for the UART.
	UDR0 = data;
}

// Send a string to the UART
void uart_printstr(const char *str)
{
	while(*str)
		uart_tx(*str++);
	uart_tx('\n');
	// <= Tab because it is automatiquely add
	uart_tx('\r');
}

void uart_init()
{
	// UBRR = F_CPU / (UART_BAUD * 16) => overflow
	uint8_t ubrr = (F_CPU / UART_BAUD / 16);

	// Set the baud rate by writing to the UBRR0 register
	UBRR0 = ubrr; 
	
	// Enable transmitter activate (TX)
	UCSR0B = (1 << TXEN0);
	
	// For 8-bit data, we set the UCSZ01 and UCSZ00 bits in the UCSR0C register.
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void set_timer1_ctc()
{
	// Mode CTC + set prescaler (slowdown the clock 1024) 
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

	// Status Register autorize interrupt (or sei())
	SREG = (1 << SREG_I);

	// Autorize interrupt on compare match A
	TIMSK1 = (1 << OCIE1A);
	
	// Reset Timer1 to 0
	TCNT1 = 0;

	// Top's Clock =>  (F_CPU / (prescaler × F_timer)) − 1
	// Prescaler => 1, 8, 64, 256, 1024
	// 16 bits => count 0 to 65535
	// Precaler = (CPU)/65535 = 122 -> 122 < 256 or 1024 => Prescaler = 1024
	// F_timer = 1/2 => 0.5hz
	// OCR1A = (16000000 / (1024 x 2)) − 1 = 31249;
	// OCR1A = 31249;
	// const uint16_t top = (F_CPU / (1024 * 0.5));
	const uint16_t top = (F_CPU / (1024 * 0.5)) - 1;

	// Set the value of OCR1A to the calculated top value
	// When TCNT1 reaches this value, the timer will reset to 0.
	OCR1A = top;
}

// Function to handle the Timer1 Compare Match A interrupt
SIGNAL (TIMER1_COMPA_vect) { uart_printstr("Hello World!"); }

int main()
{
	set_timer1_ctc();
	uart_init();

	while(1)
	{ ; }
}