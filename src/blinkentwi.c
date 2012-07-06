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
static volatile int8_t  cmd_args = 0;
static volatile int8_t  cmd_rets = 0;
static volatile int8_t  cmd_cnt  = 0;
static void           (*cmd_function)();

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

void usitwi_onStart(uint8_t read) {
	if (!read) {
		cmd_state = CMDSTATE_READ_CMD_BYTE;
	}
}

void usitwi_onStop() {
	cmd_state = CMDSTATE_READ_CMD_BYTE;
}

uint8_t usitwi_onRead() {
	if (cmd_state == CMDSTATE_WRITE_RETURN_BYTE) {
		cmd_cnt++;
		if (cmd_cnt > cmd_rets) {
			cmd_state = CMDSTATE_READ_CMD_BYTE;
		}
		return cmd_buffer[cmd_cnt-1];
	} else {
		return 0xff;
	}
}

inline void cmd_run_function() {
	cmd_function();
	if (cmd_rets < 0) {
		cmd_state = CMDSTATE_READ_CMD_BYTE;
	} else {
		cmd_state = CMDSTATE_WRITE_RETURN_BYTE;
		cmd_cnt   = 0;
	}
}

void usitwi_onWrite(uint8_t value) {
	if (cmd_state == CMDSTATE_READ_CMD_BYTE) {
		cmd_lookup(value);
		if (cmd_function != 0) {
			if (cmd_args == -1) {
				cmd_run_function();
			} else {
				cmd_state = CMDSTATE_READ_PARAM_BYTE;
				cmd_cnt   = 0;
			}
		}
	} else if (cmd_state == CMDSTATE_READ_PARAM_BYTE) {
		cmd_buffer[cmd_cnt] = value;
		cmd_cnt++;
		if (cmd_cnt > cmd_args) {
			cmd_run_function();
		}
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

