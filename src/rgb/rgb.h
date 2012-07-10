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

#ifndef _BLINKEN_TWI_RGB_H_
#define _BLINKEN_TWI_RGB_H_

#include <avr/io.h>

#ifndef min
#define min(a, b) (((a) < (b)) ? (a):(b))
#endif

#if defined( __AVR_ATtiny25__ ) | \
    defined( __AVR_ATtiny45__ ) | \
    defined( __AVR_ATtiny85__ )
#define rgb_init() {\
	DDRB   = (1 << PB1) | (1 << PB3) | (1 << PB4); \
	OCR1C  = 0xFF; \
	TCCR1  = (1 << PWM1A) | (1 << COM1A1) | (1 << CS13) | (1 << CS10); \
	GTCCR  = (1 << PWM1B) | (1 << COM1B1); \
	TCCR0A = (1 << WGM01) | (1 << WGM00); \
	TCCR0B = (1 << CS02); \
	TIMSK  = (1 << OCIE0A) | (1 << OCIE0B) | (1 << TOIE0); \
	OCR0A  = 0; \
	OCR0B  = 0; \
}
#define rgb_set_red(X) { \
	OCR0A = X; \
}
#define rgb_set_green(X) { \
	OCR1A = X; \
}
#define rgb_set_blue(X) { \
	OCR1B = X; \
}
#define rgb_get_red() OCR0B
#define rgb_get_green() OCR1A
#define rgb_get_blue() OCR1B
#endif

#endif
