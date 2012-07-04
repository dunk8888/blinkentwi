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

const rgbcmd cmdlist[2] PROGMEM = {
	{0x6e, 3, 0, toRGBNow},
	{0x67, 0, 3, getRGB}
};

void usitwi_onStart(uint8_t read) {
}

void usitwi_onStop() {
}

uint8_t usitwi_onRead() {
}

void usitwi_onWrite(uint8_t value) {
	switch(rgbstate) {
		case RGBCMD_READ_CMD_BYTE:
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

