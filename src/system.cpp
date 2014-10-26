/*
 * system.cpp
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#include "system.h"

////////////////////////////////////
// GLOBALS
////////////////////////////////////
volatile Time tmCurrentTime;
volatile Time tmAlarmTime;
volatile Date dtCurrentDate;

uint8_t nClockOverflows = 0;
volatile uint8_t nFlags = 0;

////////////////////////////////////
// FUNCTIONS
////////////////////////////////////
void * operator new (size_t size) {
	return malloc(size);
}

void operator delete(void * ptr) {
	free(ptr);
}

void InitFlags() {
/*	oFlags.bDcfFallingEdge = 0;
	oFlags.bDoAlarm = 0;
	oFlags.bRefreshDisplay = 0;
	oFlags.bSnooze = 0;*/

	nFlags = 0;
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
	 * PWM Timer for light and speaker
	 * PWM mode, no Prescaler, OC1/OC2 on
	 */
	TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1);
	TCCR1B = (1<<WGM12) | (1 << CS10);

	/* test sound and daylight output */
	OCR1A = 255;
	OCR1B = 100;		/* TODO: sound output test */

	_delay_ms(1000);

	OCR1A = 0;
	OCR1B = 0;

	/* switch off both pwm signals */
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1B1));

	/*
	 * init display
	 */
	lcd_init();
	lcd_clear();

	/*
	 * TODO: init DCF77?
	 */

	/*
	 * init "normal" clock
	 */
	TCCR0 = (1 << CS02);
	TIMSK |= (1 << TOIE0);
}

ISR(TIMER0_OVF_vect) {

	if(++nClockOverflows >= 64) {
		nClockOverflows = 0;

		/* increase the time and adjust date if needed */
		tmCurrentTime.Increase();

		if(		(tmCurrentTime.GetHour() == 0)
			&&	(tmCurrentTime.GetMinute() == 0)
			&&	(tmCurrentTime.GetSecond() == 0)) {

			dtCurrentDate.Increase();
		}

		/*oFlags.bRefreshDisplay = 1;*/

		nFlags |= FLAG_REFRESH_DISPLAY;

	}
}
