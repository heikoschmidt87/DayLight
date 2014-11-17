/*
 * system.cpp
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#include "system.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/eeprom.h>

////////////////////////////////////
// GLOBALS
////////////////////////////////////
volatile DateTime dtCurrentDateTime;
volatile DateTime tmAlarmTime;
volatile DcfData dtDcfData;
volatile LCDisplay *lcDisplay;

volatile uint8_t nMenuSecondCounter;

volatile uint8_t nClockOverflows;
volatile uint16_t nFlags;

volatile uint64_t nBitSequenceTime;
volatile uint64_t nBitTime;
volatile uint8_t nLowLevelTicks;
volatile uint8_t nCurrentBitNumber;

MenuEntry *meMenuEntries[NO_OF_MENU_ENTRIES];
LcdMenu *lmLCDMenu;

////////////////////////////////////
// FUNCTIONS
////////////////////////////////////
void InitFlags() {

	nFlags = 0;
}

void Menu_SetTime() {

	DateTime dtCurrentSetting;

	dtCurrentSetting.SetHour(dtCurrentDateTime.GetHour());
	dtCurrentSetting.SetMinute(dtCurrentDateTime.GetMinute());
	dtCurrentSetting.SetSecond(dtCurrentDateTime.GetSecond());

	bool bFunctionActive = true;
	uint8_t nCurrentVal = 0;

	char tmpPrint[3];

	lcDisplay->ShowCursor(true);
	lcDisplay->CursorBlink(true);

	do {
		/* print current setting */
		lcDisplay->CurserPos(4, 2);
		lcDisplay->WriteString(dtCurrentSetting.GetTimestring(true));
		lcDisplay->CurserPos(4, 2);

		/* set hour */
		do {

			sprintf(tmpPrint, "%.2d", dtCurrentSetting.GetHour());
			lcDisplay->WriteString(tmpPrint);
			lcDisplay->CurserPos(4, 2);

			/* wait for button press */
			while(1) {
				if(ButtonPressed(&PIN_BTN1, BUTTON_ADJUST)) {
					if(dtCurrentSetting.GetHour() == 23)
						dtCurrentSetting.SetHour(0);
					else
						dtCurrentSetting.SetHour(dtCurrentSetting.GetHour() + 1);

					break;
				}

				if(ButtonPressed(&PIN_BTN1, BUTTON_MENU)) {
					nCurrentVal = 1;
					break;
				}
			}

		}while(nCurrentVal == 0);

		/* set minute */
		do {

			lcDisplay->CurserPos(7, 2);
			sprintf(tmpPrint, "%.2d", dtCurrentSetting.GetMinute());
			lcDisplay->WriteString(tmpPrint);
			lcDisplay->CurserPos(7, 2);

			/* wait for button press */
			while(1) {
				if(ButtonPressed(&PIN_BTN1, BUTTON_ADJUST)) {
					if(dtCurrentSetting.GetMinute() == 59)
						dtCurrentSetting.SetMinute(0);
					else
						dtCurrentSetting.SetMinute(dtCurrentSetting.GetMinute() + 1);

					break;
				}

				if(ButtonPressed(&PIN_BTN1, BUTTON_MENU)) {
					nCurrentVal = 2;
					break;
				}
			}
		}while(nCurrentVal == 1);

		/* set second */
		do {

			lcDisplay->CurserPos(10, 2);
			sprintf(tmpPrint, "%.2d", dtCurrentSetting.GetSecond());
			lcDisplay->WriteString(tmpPrint);
			lcDisplay->CurserPos(10, 2);

			/* wait for button press */
			while(1) {
				if(ButtonPressed(&PIN_BTN1, BUTTON_ADJUST)) {
					if(dtCurrentSetting.GetSecond() == 59)
						dtCurrentSetting.SetSecond(0);
					else
						dtCurrentSetting.SetSecond(dtCurrentSetting.GetSecond() + 1);

					break;
				}

				if(ButtonPressed(&PIN_BTN1, BUTTON_MENU)) {
					nCurrentVal = 3;
					bFunctionActive = false;
					break;
				}
			}

		}while(nCurrentVal == 2);

	}while(bFunctionActive);

	dtCurrentDateTime.SetHour(dtCurrentSetting.GetHour());
	dtCurrentDateTime.SetMinute(dtCurrentSetting.GetMinute());
	dtCurrentDateTime.SetSecond(dtCurrentSetting.GetSecond());

	lcDisplay->ShowCursor(false);
	lcDisplay->CursorBlink(false);
}

void Menu_SetDate() {
	lcDisplay->WriteString("Set Date");

	_delay_ms(2000);
}

void Menu_SetAlarm() {

	DateTime dtCurrentSetting;

	dtCurrentSetting.SetHour(tmAlarmTime.GetHour());
	dtCurrentSetting.SetMinute(tmAlarmTime.GetMinute());
	dtCurrentSetting.SetSecond(tmAlarmTime.GetSecond());

	bool bFunctionActive = true;
	uint8_t nCurrentVal = 0;

	char tmpPrint[3];

	lcDisplay->ShowCursor(true);
	lcDisplay->CursorBlink(true);

	do {
		/* print current setting */
		lcDisplay->CurserPos(4, 2);
		lcDisplay->WriteString(dtCurrentSetting.GetTimestring(true));
		lcDisplay->CurserPos(4, 2);

		/* set hour */
		do {

			sprintf(tmpPrint, "%.2d", dtCurrentSetting.GetHour());
			lcDisplay->WriteString(tmpPrint);
			lcDisplay->CurserPos(4, 2);

			/* wait for button press */
			while(1) {
				if(ButtonPressed(&PIN_BTN1, BUTTON_ADJUST)) {
					if(dtCurrentSetting.GetHour() == 23)
						dtCurrentSetting.SetHour(0);
					else
						dtCurrentSetting.SetHour(dtCurrentSetting.GetHour() + 1);

					break;
				}

				if(ButtonPressed(&PIN_BTN1, BUTTON_MENU)) {
					nCurrentVal = 1;
					break;
				}
			}

		}while(nCurrentVal == 0);

		/* set minute */
		do {

			lcDisplay->CurserPos(7, 2);
			sprintf(tmpPrint, "%.2d", dtCurrentSetting.GetMinute());
			lcDisplay->WriteString(tmpPrint);
			lcDisplay->CurserPos(7, 2);

			/* wait for button press */
			while(1) {
				if(ButtonPressed(&PIN_BTN1, BUTTON_ADJUST)) {
					if(dtCurrentSetting.GetMinute() == 59)
						dtCurrentSetting.SetMinute(0);
					else
						dtCurrentSetting.SetMinute(dtCurrentSetting.GetMinute() + 1);

					break;
				}

				if(ButtonPressed(&PIN_BTN1, BUTTON_MENU)) {
					nCurrentVal = 2;
					break;
				}
			}
		}while(nCurrentVal == 1);

		/* set second */
		do {

			lcDisplay->CurserPos(10, 2);
			sprintf(tmpPrint, "%.2d", dtCurrentSetting.GetSecond());
			lcDisplay->WriteString(tmpPrint);
			lcDisplay->CurserPos(10, 2);

			/* wait for button press */
			while(1) {
				if(ButtonPressed(&PIN_BTN1, BUTTON_ADJUST)) {
					if(dtCurrentSetting.GetSecond() == 59)
						dtCurrentSetting.SetSecond(0);
					else
						dtCurrentSetting.SetSecond(dtCurrentSetting.GetSecond() + 1);

					break;
				}

				if(ButtonPressed(&PIN_BTN1, BUTTON_MENU)) {
					nCurrentVal = 3;
					bFunctionActive = false;
					break;
				}
			}

		}while(nCurrentVal == 2);

	}while(bFunctionActive);

	tmAlarmTime.SetHour(dtCurrentSetting.GetHour());
	tmAlarmTime.SetMinute(dtCurrentSetting.GetMinute());
	tmAlarmTime.SetSecond(dtCurrentSetting.GetSecond());

	eeprom_write_block((void*)&tmAlarmTime, (void*)0, sizeof(DateTime));

	lcDisplay->ShowCursor(false);
	lcDisplay->CursorBlink(false);
}

void Menu_SwitchAlarm() {

	bool bFunctionActive = true;

	lcDisplay->ShowCursor(true);
	lcDisplay->CursorBlink(true);

	do {
		/* print current setting */
		lcDisplay->CurserPos(6, 2);

		if((nFlags & FLAG_DO_ALARM) > 0) {
			lcDisplay->WriteString("On ");
		} else {
			lcDisplay->WriteString("Off");
		}

		lcDisplay->CurserPos(6, 2);

		/* wait for next button press */
		while(1) {

			/* check for adjust button */
			if(ButtonPressed(&PIN_BTN1, BUTTON_ADJUST)) {
				nFlags ^= FLAG_DO_ALARM;
				break;
			}

			if(ButtonPressed(&PIN_BTN1, BUTTON_MENU)) {
				bFunctionActive = false;
				break;
			}
		}

	} while(bFunctionActive);

	eeprom_write_block((void*)&nFlags, (void*)(sizeof(DateTime) + 1), sizeof(nFlags));

	lcDisplay->ShowCursor(false);
	lcDisplay->CursorBlink(false);
}

void Menu_SetSnoozeTime() {
	lcDisplay->WriteString("Set Snooze Time");

	_delay_ms(2000);

}

void Menu_SwitchDCF() {
	bool bFunctionActive = true;

	lcDisplay->ShowCursor(true);
	lcDisplay->CursorBlink(true);

	do {
		/* print current setting */
		lcDisplay->CurserPos(6, 2);

		if((nFlags & FLAG_DO_DCF_RECV) > 0) {
			lcDisplay->WriteString("On ");
		} else {
			lcDisplay->WriteString("Off");
		}

		lcDisplay->CurserPos(6, 2);

		/* wait for next button press */
		while(1) {

			/* check for adjust button */
			if(ButtonPressed(&PIN_BTN1, BUTTON_ADJUST)) {
				nFlags ^= FLAG_DO_DCF_RECV;
				break;
			}

			if(ButtonPressed(&PIN_BTN1, BUTTON_MENU)) {
				bFunctionActive = false;
				break;
			}
		}

	} while(bFunctionActive);

	lcDisplay->ShowCursor(false);
	lcDisplay->CursorBlink(false);
}

void InitDayLightAlarm() {

	/*
	 * init flags
	 */
	/* TODO: read from EEPROM */
	nFlags |= FLAG_DO_DCF_RECV;

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
	LcdHwConfig_t oHwConfig;

	oHwConfig.nLcdPort = &PORT_LCD;
	oHwConfig.nLcdDdr = &DDR_LCD;
	oHwConfig.nLcdStartPin = LCD_DB;
	oHwConfig.nLcdRS = LCD_RS;
	oHwConfig.nLcdEn = LCD_EN;

	oHwConfig.nDispLightPort = &PORT_DISPLIGHT;
	oHwConfig.nDispLightDdr = &DDR_DISPLIGHT;
	oHwConfig.nDispLightPin = DISPLAY_LIGHT;

	lcDisplay = new LCDisplay(oHwConfig);

	lcDisplay->InitLCDisplay();
	lcDisplay->ClearLCDisplay();


	/*
	 * init DCF77
	 */
	/* set input for external Interrupt */
	DDRD &= ~(1 << PD2);

	/* timer for DCF77 bit decoding */
	TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << WGM21);		// Prescaler 256 and CTC mode
	TIMSK |= (1 << OCIE2);									// ISR on compare match
	TCNT2 = 0;
	OCR2 = 90;												// TODO: correction value!

	/* INT0 external interrupt for getting bit time -- arm rising edge initially */
	MCUCR |= (1 << ISC01) | (1 << ISC00);
	GICR |= (1 << INT0);

	/*
	 * init "normal" clock
	 */
	TCCR0 = (1 << CS02);
	TIMSK |= (1 << TOIE0);

	/*
	 * init menu
	 */
	meMenuEntries[5] = new MenuEntry("** DCF an/aus **", Menu_SwitchDCF, 0);
	meMenuEntries[4] = new MenuEntry("** Snooze Zeit *", Menu_SetSnoozeTime, meMenuEntries[5]);
	meMenuEntries[3] = new MenuEntry("* Alarm an/aus *", Menu_SwitchAlarm, meMenuEntries[4]);
	meMenuEntries[2] = new MenuEntry("*** Weckzeit ***", Menu_SetAlarm, meMenuEntries[3]);
	meMenuEntries[1] = new MenuEntry("***** Datum ****", Menu_SetDate, meMenuEntries[2]);
	meMenuEntries[0] = new MenuEntry("***** Zeit *****", Menu_SetTime, meMenuEntries[1]);
	meMenuEntries[5]->SetNext(meMenuEntries[0]);

	ButtonConfig_t btnConfig;
	btnConfig.btnPin_ = &PIN_BTN1;
	btnConfig.btnNext_ = BUTTON_ADJUST;
	btnConfig.btnEnter_ = BUTTON_MENU;

	lmLCDMenu = new LcdMenu(btnConfig, lcDisplay, meMenuEntries[0], &nMenuSecondCounter);

	/*
	 * init eeprom variables
	 */
	eeprom_read_block((void*)&tmAlarmTime, (const void*)0, sizeof(DateTime));

	uint16_t nLocalFlags = 0;
	eeprom_read_block((void*)&nLocalFlags, (const void*)(sizeof(DateTime) + 1), sizeof(nLocalFlags));
	nFlags = (nLocalFlags & FLAG_DO_ALARM) | (nLocalFlags & FLAG_DO_DCF_RECV);
}

ISR(TIMER0_OVF_vect) {

	if(++nClockOverflows >= 64) {
		nClockOverflows = 0;

		nMenuSecondCounter++;

		/* increase the time and adjust date if needed */
		dtCurrentDateTime.Increase();

		if(		(dtCurrentDateTime.GetHour() == 0)
			&&	(dtCurrentDateTime.GetMinute() == 0)
			&&	(dtCurrentDateTime.GetSecond() == 0)) {
		}

		nFlags |= FLAG_REFRESH_DISPLAY;
	}
}

ISR(INT0_vect) {

	/* disable external interrupt while handling */
	GICR &= ~(1 << INT0);

	if((nFlags & FLAG_DCF_FALLING_EDGE) > 0) {

		/* a new bit starts */
		nBitSequenceTime = nBitTime;	/* this is the total number of ticks between two bits */
		nBitTime = 0;					/* this holds the bit time */

		/* arm on the rising edge to determine the bit time */
		nFlags &= ~FLAG_DCF_FALLING_EDGE;
		MCUCR |= (1 << ISC01) | (1 << ISC00);

		/* toggle the symbol for DCF77 signal receiving */
		nFlags |= FLAG_UPDATE_DCF_DOT;

		/* determine if there is a minute change */
		if(nBitSequenceTime > 250) {

			/* check if all bits have been received -- only then update free running time */
			/* TODO: correct again with new controller */
			if(nCurrentBitNumber == 59) {
				/* make the DCF data to update the time */
				nFlags |= FLAG_REFRESH_DCFTIME;

				/* TODO: evaluate time here? */
				dtDcfData.EvaluateDateTime(true);

				/* reset the free running second timer */
				nClockOverflows = 0;
				TCNT0 = 0;
				dtCurrentDateTime.SetSecond(0);
			}

			/* reset the current bit number */
			nCurrentBitNumber = 0;
		}

	} else {

		/* save the low level bit time and therefore the bit value
		 * 200ms --> "1", 100ms --> "0" */
		nLowLevelTicks = nBitTime;

		/* add the bit to the DCF77 structure */
		if(nLowLevelTicks > 30) {
			dtDcfData.AddBit(nCurrentBitNumber, 1);
		} else {
			dtDcfData.AddBit(nCurrentBitNumber, 0);
		}

		/* increase the current bit number */
		nCurrentBitNumber++;

		/* react in falling edge at INT0 again */
		nFlags |= FLAG_DCF_FALLING_EDGE;

		MCUCR |= (1 << ISC01);
		MCUCR &= ~(1 << ISC00);
	}


	GICR |= (1 << INT0);
}

ISR(TIMER2_COMP_vect) {
	/* increase the bit time */
	nBitTime++;
}
