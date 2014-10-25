/*
 * system.cpp
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#include "system.h"

void * operator new (size_t size) {
	return malloc(size);
}

void operator delete(void * ptr) {
	free(ptr);
}

void InitFlags() {
	oFlags.bDcfFallingEdge = 0;
	oFlags.bDoAlarm = 0;
	oFlags.bRefreshDisplay = 0;
	oFlags.bSnooze = 0;
}

void InitDayLightAlarm() {
	/*
	 * init buttons
	 */

	/* set outputs */
	DDR_BTN1 &= ~((1 << BUTTON_SNOOZE) | (1 << BUTTON_MENU) | (1 << BUTTON_ADJUST));
	DDR_BTN2 &= ~(1 << BUTTON_LIGHT);

	/* activate internal pullups */
	PORT_BTN1 |= (1 << BUTTON_SNOOZE) | (1 << BUTTON_MENU) | (1 << BUTTON_ADJUST);
	PORT_BTN2 |= (1 << BUTTON_LIGHT);


	/*
	 * init DayLight
	 */
	DDR_DAY_LIGHT |= (1 << DAY_LIGHT);
	PORT_DAY_LIGHT &= ~(1 << DAY_LIGHT);

	/* test daylight */
	PORT_DAY_LIGHT |= (1 << DAY_LIGHT);
	_delay_ms(1000);
	PORT_DAY_LIGHT &= ~(1 << DAY_LIGHT);


	/*
	 * init speaker
	 */
	DDR_SPEAKER |= (1 << SPEAKER);
	PORT_SPEAKER &= (1 << SPEAKER);

	/* TODO: test speaker */

	/*
	 * init display light
	 */
	DDR_DISPLIGHT |= (1 << DISPLAY_LIGHT);
	PORT_DISPLIGHT &= ~(1 << DISPLAY_LIGHT);

	/* play test tone */
	/*
	 * TODO: PWM Timer for light and speaker
	 */

	/*
	 * TODO: init display
	 */

	/*
	 * TODO: init DCF77?
	 */
}
