/*

Copyright 2012 Niclas Hoyer    <niclas at verbugt.de>

This file is part of Blinkentwi.

Blinkentwi is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Blinkentwi is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Blinkentwi.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "rgb.h"

volatile uint8_t rgb_pwm_target_red   = 0;
volatile uint8_t rgb_pwm_target_green = 0;
volatile uint8_t rgb_pwm_target_blue  = 0;
volatile uint8_t rgb_pwm_fade         = 0;

#define rgb_fade(X, Y) { \
	if (X != Y) { \
		if (X > Y) { \
			X -= min(X - Y, rgb_pwm_fade); \
		} else { \
			X += min(Y - X, rgb_pwm_fade); \
		} \
	} \
} \

#if defined( __AVR_ATtiny25__ ) | \
    defined( __AVR_ATtiny45__ ) | \
    defined( __AVR_ATtiny85__ )

ISR(TIMER0_OVF_vect) {
	
	if (rgb_pwm_fade > 0) {
		rgb_fade(rgb_get_red(),   rgb_pwm_target_red);
		rgb_fade(rgb_get_green(), rgb_pwm_target_green);
		rgb_fade(rgb_get_blue(),  rgb_pwm_target_blue);
	}

	if (OCR0A != 0) {
		PORTB |= (1 << PB3);
	}
}

ISR(TIMER0_COMPA_vect) {
	PORTB &= ~(1 << PB3);
}

#endif

