#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "../lib/usitwi/src/slave.h"

typedef enum {
	RGBCMD_READ_CMD_BYTE,
	RGBCMD_READ_PARAM_BYTE,
	RGBCMD_WRITE_RETURN_BYTE
} rgbstate_t;

static volatile rgbstate_t rgbstate = RGBCMD_READ_CMD_BYTE;

typedef struct {
	uint8_t cmd;
	uint8_t args;
	uint8_t retvals;
	void (*function)();
} rgbcmd;

static volatile uint8_t valbuffer[7];
static volatile uint8_t valcnt = 0;

void toRGBNow() {
}

void getRGB() {
}

const rgbcmd cmdlist[] PROGMEM = {
	{0x6e, 3, 0, toRGBNow},
	{0x67, 0, 3, getRGB}
};

inline uint8_t lookupcmd(uint8_t value, rgbcmd* cmd) {
	uint8_t i;
	for (i=0; i<sizeof(cmdlist); i++) {
		memcpy_P(cmd, &cmdlist[i], sizeof(rgbcmd));
		if (cmd->cmd == value) {
			return 1;
		}
	}
	return 0;
}

void usitwi_onStart(uint8_t read) {
}

void usitwi_onStop() {
}

uint8_t usitwi_onRead() {
}

void usitwi_onWrite(uint8_t value) {
	rgbcmd cmd;
	switch(rgbstate) {
		case RGBCMD_READ_CMD_BYTE:
			if (lookupcmd(value, &cmd)) {
				if (cmd.args == 0) {
					cmd.function();
					if (cmd.retvals > 0) {
						valcnt = cmd.retvals;
						rgbstate = RGBCMD_WRITE_RETURN_BYTE;
					}
				} else {
					valcnt = cmd.args;
					rgbstate = RGBCMD_READ_PARAM_BYTE;
				}
			}
		break;
		case RGBCMD_READ_PARAM_BYTE:
		break;
		case RGBCMD_WRITE_RETURN_BYTE:
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

