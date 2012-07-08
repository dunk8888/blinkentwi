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

#ifndef _BLINKEN_TWI_RND_H_
#define _BLINKEN_TWI_RND_H_

#include <avr/io.h>
#include <stdlib.h>

#define rnd_init() { \
	unsigned short seed = 0; \
	unsigned short *p = (unsigned short*) (RAMEND+1); \
	extern unsigned short __heap_start; \
	while (p >= &__heap_start + 1) { \
		seed ^= * (--p); \
	} \
	srandom(seed); \
}

#define rnd_get() random()

#endif
