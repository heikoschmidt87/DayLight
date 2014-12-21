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

	lcDisplay->SetDisplayLight(true);

	/* set display light on for 10 seconds */
	nDisplayLightCountdown = 10;

	sei();

	while(1) {

		DoDcfRefresh();

		DoDisplayRefresh();

		DoAlarmHandling();

		DoButtonHandling();

		/* check if button has been released */
		if(!bMenuStartAllowed) {
			if(!ButtonPressed(&PIN_BTN1, BUTTON_MENU))
				bMenuStartAllowed = true;
		}
	}


	return 0;
}

