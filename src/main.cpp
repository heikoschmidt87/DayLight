/*
 * main.cpp
 *
 *  Created on: 22.10.2014
 *      Author: heiko
 */

#include <avr/io.h>

#include "system.h"

/**
 *
 * @return
 */
int main() {

	InitDayLightAlarm();

	PORT_DISPLIGHT |= (1 << DISPLAY_LIGHT);

	sei();

	while(1) {

		/* refresh the display */
		if(nFlags & FLAG_REFRESH_DISPLAY > 0) {

			nFlags &= ~FLAG_REFRESH_DISPLAY;

			lcd_home();
			lcd_string(tmCurrentTime.GetTimestring(true));
		}
	}


	return 0;
}

