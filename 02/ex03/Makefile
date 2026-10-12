CFLAGS			=	-Wall -Wextra -Werror

CC				=	avr-gcc

# **************************************************************************** #
#                                                                              #
#                                  SOURCES                                     #
#                                                                              #
# **************************************************************************** #

# Target file
TARGET		=	main

SRC			=	$(TARGET).c

BINS		=	$(TARGET).bin 

HEXS		=	$(TARGET).hex 
	
# **************************************************************************** #
#                                                                              #
#                                  RULES                                       #
#                                                                              #
# **************************************************************************** #

# MCU name
MCU = atmega328p

# Processor frequency
F_CPU = 16000000

AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PORT = /dev/serial/by-id/usb-1a86_USB_Serial-if00-port0

all:  hex flash

hex: 
	avr-gcc -g -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os $(CFLAGS) $(SRC) -o $(BINS)
	avr-objcopy -O ihex $(BINS) $(HEXS)

flash:
	avrdude -p $(MCU) -c $(AVRDUDE_PROGRAMMER) -P $(AVRDUDE_PORT) -b 115200 -U flash:w:$(HEXS):i

clean:
	@rm -r $(BINS) $(HEXS)

fclean:
	@rm -r $(BINS) $(HEXS)
	@printf "$\nCleaned\n$"

re: fclean all

.PHONY: fclean clean all re


