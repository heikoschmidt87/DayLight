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

	Time tmTest;


	while(1) {

		/* refresh the display */
		if(oFlags.bRefreshDisplay) {
			oFlags.bRefreshDisplay = 0;
		}


		//tmCurrentTime.Increase();
		tmTest.Increase();

		lcd_home();
		lcd_string(tmTest.GetTimestring(true));
		_delay_ms(1000);
	}


	return 0;
}

