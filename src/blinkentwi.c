#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "rgb/rgb.h"

uint8_t usitwi_address = 0x42;

int main() {
	rgb_init();
	usitwi_init();
	sei();
	while (1) {
	}
}

