#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t cmd_buffer[7];
volatile int8_t  cmd_args = 0;
volatile int8_t  cmd_rets = 0;
void           (*cmd_function)();

void toRGBNow() {
}

void getRGB() {
	cmd_buffer[0] = 0x42;
	cmd_buffer[1] = 0x43;
	cmd_buffer[2] = 0x44;
	
	PORTB ^= (1 << PB1);
}

inline void cmd_lookup(uint8_t cmd) {
	if        ( cmd == 0x6e ) {
		cmd_args     = 2;
		cmd_rets     = -1;
		cmd_function = toRGBNow;
	} else if ( cmd == 0x67 ) {
		cmd_args     = -1;
		cmd_rets     = 2;
		cmd_function = getRGB;
	} else {
		cmd_function = 0;
	}
}

uint8_t usitwi_address = 0x42;

int main() {
	
	DDRB = (1 << PB1);

	usitwi_init();

	sei();

	while (1) {
	}
}

