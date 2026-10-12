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

char uart_rx()
{
	// Wait for data to be received
	while (! (UCSR0A & (1 << RXC0))) ;
	
	// Get and return received data from buffer
	return (UDR0);
}

void uart_init()
{
	// UBRR = F_CPU / (UART_BAUD * 16) => overflow
	uint8_t ubrr = (F_CPU / UART_BAUD / 16);

	// Set the baud rate by writing to the UBRR0 register
	UBRR0 = ubrr; 
	
	// Mode USART_RX
	UCSR0A = (1 << RXC0);

	// Enable transmitter activate (TX) and receiver (RX)
	// RXCIE0 = autorize interrupt
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
	
	// For 8-bit data, we set the UCSZ01 and UCSZ00 bits in the UCSR0C register.
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Function to handle the Timer1 Compare Match A interrupt
SIGNAL (USART_RX_vect)
{
	// Read the received data from the UDR0 register
	uint8_t c = uart_rx();
	
	if (c >= 'a' && c <= 'z')
		c = (c + 'A' - 'a'); // Convert to uppercase
	else if (c >= 'A' && c <= 'Z')
		c = (c + 'a' - 'A'); // Convert to lowercase

	// Echo the received data back to the UART
	uart_tx(c);
}

int main()
{
	uart_init();

	// Status Register autorize interrupt (or sei())
	SREG = (1 << SREG_I);

	while(1)
	{ ; }
}