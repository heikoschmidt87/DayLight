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
/*		if((nFlags & FLAG_REFRESH_DISPLAY) > 0) {

			nFlags &= ~FLAG_REFRESH_DISPLAY;

			lcd_home();
			lcd_string(tmCurrentTime.GetTimestring(true));
		}
*/
/*		if((nFlags & FLAG_REFRESH_DCFTIME) > 0) {

			nFlags &= ~FLAG_REFRESH_DCFTIME;

			lcd_setcursor(0, 2);
			lcd_string(tmDcfData.GetTimestring(true));
		}*/
	}


	return 0;
}

