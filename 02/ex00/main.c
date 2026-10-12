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

void uart_init(uint8_t ubrr)
{
	// Set the baud rate by writing to the UBRR0 register
	UBRR0 = ubrr; 
	
	// Enable transmitter activate (TX)
	UCSR0B = (1 << TXEN0);
	
	// For 8-bit data, we set the UCSZ01 and UCSZ00 bits in the UCSR0C register.
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

int main()
{
	// Calculate the UBRR value based on the CPU frequency and desired baud rate.
	// UBRR = F_CPU / (UART_BAUD * 16) => overflow
	uint8_t ubrr = (F_CPU / UART_BAUD / 16);
	
	uart_init(ubrr);

	while(1)
	{
		uart_tx('Z');
		_delay_ms(1000);
	}
}