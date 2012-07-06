#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../lib/usitwi/src/slave.h"

typedef enum {
	CMDSTATE_READ_CMD_BYTE,
	CMDSTATE_READ_PARAM_BYTE,
	CMDSTATE_WRITE_RETURN_BYTE
} cmd_state_t;

static volatile cmd_state_t cmd_state = CMDSTATE_READ_CMD_BYTE;

static volatile uint8_t cmd_buffer[7];
static volatile uint8_t cmd_args = 0;
static volatile uint8_t cmd_rets = 0;
static void           (*cmd_function)();

void toRGBNow() {
}

void getRGB() {
}

inline void cmd_lookup(uint8_t cmd) {
	if        ( cmd == 0x6e ) {
		cmd_args     = 3;
		cmd_rets     = 0;
		cmd_function = toRGBNow;
	} else if ( cmd == 0x67 ) {
		cmd_args     = 0;
		cmd_rets     = 3;
		cmd_function = getRGB;
	} else {
		cmd_function = 0;
	}
}

void usitwi_onStart(uint8_t read) {
}

void usitwi_onStop() {
	cmd_state = CMDSTATE_READ_CMD_BYTE;
}

uint8_t usitwi_onRead() {
}

void usitwi_onWrite(uint8_t value) {
	switch(cmd_state) {
		case CMDSTATE_READ_CMD_BYTE:
			cmd_lookup(value);
			if (cmd_function != 0) {
				if (cmd_args == 0) {
					cmd_function();
					if (cmd_rets > 0) {
						cmd_state = CMDSTATE_WRITE_RETURN_BYTE;
					} else {
						cmd_state = CMDSTATE_READ_CMD_BYTE;
					}
				} else {
					cmd_state = CMDSTATE_READ_PARAM_BYTE;
				}
			}
		break;
		case CMDSTATE_READ_PARAM_BYTE:
		break;
		case CMDSTATE_WRITE_RETURN_BYTE:
		break;
	}
}

uint8_t usitwi_address = 0x42;

int main() {
	usitwi_init();

	sei();

	while (1) {
	}
}

