/*
 * main.cpp
 *
 *  Created on: 22.10.2014
 *      Author: heiko
 */

#include <avr/io.h>

#include "system.h"


/*
 * symbols
 */
uint8_t chrDCFOn_1[8] = {
		0x00000000,
		0b00000100,
		0b00001010,
		0b00000000,
		0b00000100,
		0b00000100,
		0b00001110,
		0b00011111
};

uint8_t chrDCFOn_2[8] = {
		0x00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000100,
		0b00000100,
		0b00001110,
		0b00011111
};

uint8_t chrDCFOff[8] = {
		0x00000000,
		0b00001010,
		0b00000100,
		0b00001010,
		0b00000100,
		0b00000100,
		0b00001110,
		0b00011111
};

uint8_t chrAlarmOn[8] = {
		0x00000000,
		0b00000100,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00011111,
		0b00000100,
		0b00000000
};

/**
 *
 * @return
 */
int main() {

	InitDayLightAlarm();

	lcDisplay->SetDisplayLight(true);

	/*
	 * generate own chars
	 */
	lcDisplay->GenerateChar(LCD_GC_CHAR0, chrDCFOn_1);
	lcDisplay->GenerateChar(LCD_GC_CHAR1, chrDCFOn_2);
	lcDisplay->GenerateChar(LCD_GC_CHAR2, chrDCFOff);
	lcDisplay->GenerateChar(LCD_GC_CHAR3, chrAlarmOn);

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

