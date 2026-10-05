# TARGET = firmware
# CC = avr-gcc
# # CFLAGS = -Wall $(MCU) $(F_CPU)

# # MCU = atmega328p
# # F_CPU = 16000000UL
# AVRDUDE = avrdude
# OBJCOPY = avr-objcopy
# BIN = $(TARGET).bin
# SRC = main.c
# OBJ = $(SRC:.c=.o)

# all: hex

# hex: $(TARGET).hex

# %.hex: %.elf
# 	$(OBJCOPY) -O ihex $< $@

# $(TARGET).elf: $(OBJ)
# 	$(CC) -o $@ $^

# %.o: %.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

# flash: hex
# 	$(AVRDUDE) -U flash:w:$(TARGET).hex:i
	
# clean:
# 	rm -rf *.o *.elf *.hex

# .PHONY: all hex flash clean

# TARGET=main
# CC=avr-gcc
# CFLAGS=-Os -DF_CPU=16000000UL -mmcu=$(MCU)

# BIN = $(TARGET).bin
# PORT=/dev/ttyACM0
# MCU = atmega328p
# LDFLAGS=-Wl,-gc-sections -Wl,-relax
# OBJECT_FILES=main.o

# all: $(TARGET).bin

# $(TARGET).bin: $(TARGET).hex
# 	objcopy -I ihex -O binary $(TARGET).hex $(TARGET).bin

# %.hex: %.obj
# 	avr-objcopy -R .eeprom -O ihex $< $@

# %.obj: $(OBJECT_FILES)
# 	$(CC) $(CFLAGS) $(OBJECT_FILES) $(LDFLAGS) -o $@

# flash: $(TARGET).hex
# 	avrdude -p $(MCU) -c avr109 -P $(PORT) -U flash:w:$(TARGET).hex

# clean:
# 	rm -f *.o *.hex *.obj *.hex *.bin

TARGET=main
MCU = atmega328p
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=$(MCU)
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
	rm -f *.o *.hex *.obj *.bin