TARGET=main
MCU = atmega328p
CC=avr-gcc
F_CPU = 16000000UL
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
LDFLAGS=-Wl,-gc-sections -Wl,-relax
BAUD=115200
PORT=/dev/ttyUSB0
OBJECT_FILES=main.o

all: $(TARGET).hex

$(TARGET).bin: $(TARGET).hex
	$(OBJCOPY) -I ihex -O binary $(TARGET).hex $(TARGET).bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.hex: %.obj
	$(OBJCOPY) -R .eeprom -O ihex $< $@

$(TARGET).obj: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) $(LDFLAGS) -o $@

flash: $(TARGET).hex
	avrdude -F -V -p $(MCU) -c arduino  -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex:i

clean:
	rm -f *.o *.hex *.obj