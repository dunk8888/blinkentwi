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

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../lib/usitwi/src/slave.h"
#include "rgb/rgb.h"

uint8_t usitwi_address = 0x42;

int main() {
	rgb_init();
	usitwi_init();
	sei();
	while (1) {
	}
}

