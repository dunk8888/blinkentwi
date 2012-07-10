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

volatile uint8_t cmd_buffer[7];
volatile int8_t  cmd_args = 0;
volatile int8_t  cmd_rets = 0;
void           (*cmd_function)();

extern void getVersion();
extern void fadeToRandomRGB();
extern void fadeToRGB();
extern void getRGB();
extern void toRGBNow();

void cmd_lookup(uint8_t cmd) {
	if        ( cmd == 0x5a ) {
		cmd_args     = -1;
		cmd_rets     = 0;
		cmd_function = getVersion;
	} else if ( cmd == 0x43 ) {
		cmd_args     = -1;
		cmd_rets     = -1;
		cmd_function = fadeToRandomRGB;
	} else if ( cmd == 0x63 ) {
		cmd_args     = 2;
		cmd_rets     = -1;
		cmd_function = fadeToRGB;
	} else if ( cmd == 0x67 ) {
		cmd_args     = -1;
		cmd_rets     = 2;
		cmd_function = getRGB;
	} else if ( cmd == 0x6e ) {
		cmd_args     = 2;
		cmd_rets     = -1;
		cmd_function = toRGBNow;
	} else {
		cmd_function = 0;
	}
}

