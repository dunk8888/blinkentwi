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
#include "../rgb/rgb.h"

extern volatile uint8_t cmd_buffer[7];
extern volatile uint8_t rgb_pwm_target_red;
extern volatile uint8_t rgb_pwm_target_green;
extern volatile uint8_t rgb_pwm_target_blue;
extern volatile uint8_t rgb_pwm_fade;

void fadeToRGB() {
	rgb_pwm_target_red   = cmd_buffer[0];
	rgb_pwm_target_green = cmd_buffer[1];
	rgb_pwm_target_blue  = cmd_buffer[2];
	rgb_pwm_fade         = 1;
}

