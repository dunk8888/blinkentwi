MMCU=attiny85
CC=avr-gcc
OBJCPY=avr-objcopy
AVRDUDE=avrdude
AVRSIZE=avr-size

compile:
	$(CC) -mmcu=$(MMCU) -Os -g src/blinkentwi.c src/cmd/*.c lib/usitwi/src/slave.c lib/usitwi/src/cmd.c -o out/blinkentwi.elf
	$(OBJCPY) -j .text -j .data -O ihex out/blinkentwi.elf out/blinkentwi.hex
#	$(OBJCPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex out/blinkentwi.elf out/blinkentwi.eeprom.hex
	$(AVRSIZE) -A -t out/blinkentwi.elf

program:
	$(AVRDUDE) -p $(MMCU) -v -e -U flash:w:out/blinkentwi.hex

clean:
	rm -f out/*.o out/*.elf out/*.hex
