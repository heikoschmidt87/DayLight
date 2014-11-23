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

volatile bool bMenuStartAllowed = true;


MenuEntry *meMenuEntries[NO_OF_MENU_ENTRIES];
LcdMenu *lmLCDMenu;


static const uint16_t nLinearMapping[] = {	900, 896, 892, 888, 884, 880, 876, 872, 868, 864, 860, 856, 852, 848, 844, 840, 836, 832, 828, 824,
											820, 816, 812, 808, 804, 800, 796, 792, 788, 784, 780, 776, 772, 768, 764, 763, 760, 756, 752, 748,
											744, 740, 736, 732, 728, 724, 720, 716, 712, 708, 704, 700, 696, 692, 688, 684, 680, 676, 672, 668,
											664, 660, 656, 652, 648, 644, 640, 636, 632, 628, 624, 620, 616, 612, 608, 604, 600, 596, 592, 588,
											584, 580, 576, 572, 568, 564, 560, 556, 552, 548, 544, 540, 536, 532, 528, 524, 520, 516, 512, 508,
											504, 500, 496, 492, 488, 484, 480, 476, 472, 468, 464, 460, 456, 452, 448, 444, 440, 436, 432, 428,
											424, 420, 416, 412, 408, 404, 400, 396, 392, 388, 384, 380, 376, 375, 372, 368, 364, 360, 356, 352,
											348, 344, 340, 336, 332, 328, 324, 320, 316, 312, 308, 304, 300
											};

static const uint16_t nExpMapping[] = {	152, 153, 154, 154, 155, 156, 156, 157, 158, 159, 159, 160, 161, 162, 162, 163, 164, 165, 166, 166,
										167, 168, 169, 170, 171, 172, 172, 173, 174, 175, 176, 177, 178, 179, 179, 180, 181, 182, 183, 184,
										185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 201, 202, 203, 204, 205,
										206, 207, 208, 210, 211, 212, 213, 214, 215, 217, 218, 219, 220, 222, 223, 224, 225, 227, 228, 229,
										231, 232, 233, 235, 236, 237, 239, 240, 242, 243, 244, 246, 247, 249, 250, 252, 253, 255, 256, 258,
										259, 261, 263, 264, 266, 267, 269, 271, 272, 274, 276, 277, 279, 281, 283, 284, 286, 288, 290, 291,
										293, 295, 297, 299, 301, 303, 305, 306, 308, 310, 312, 314, 316, 318, 320, 322, 325, 327, 329, 331,
										333, 335, 337, 340, 342, 344, 346, 348, 351, 353, 355, 358, 360, 362, 365, 367, 370, 372, 375, 377,
										380, 382, 385, 387, 390, 392, 395, 398, 400, 403, 406, 409, 411, 414, 417, 420, 423, 425, 428, 431,
										434, 437, 440, 443, 446, 449, 452, 456, 459, 462, 465, 468, 472, 475, 478, 481, 485, 488, 492, 495,
										498, 502, 505, 509, 513, 516, 520, 523, 527, 531, 535, 538, 542, 546, 550, 554, 558, 562, 566, 570,
										574, 578, 582, 586, 590, 594, 599, 603, 607, 612, 616, 621, 625, 630, 634, 639, 643, 648, 653, 657,
										662, 667, 672, 677, 681, 686, 691, 696, 702, 707, 712, 717, 722, 728, 733, 738, 744, 749, 755, 760,
										766, 771, 777, 783, 789, 794, 800, 806, 812, 818, 824, 830, 836, 843, 849, 855, 861, 868, 874, 881,
										887, 894, 901, 907, 914, 921, 928, 935, 942, 949, 956, 963, 970, 978, 985, 992, 1000, 1007, 1023, 1023
										};

////////////////////////////////////
// FUNCTIONS
////////////////////////////////////
void InitFlags() {

	nFlags = 0;
}

void DoDcfRefresh() {

	/* check for refreshing DCF77 info */
	if(		((nFlags & FLAG_REFRESH_DCFTIME) > 0)
		&&	((nFlags & FLAG_DO_DCF_RECV) > 0)) {

		nFlags &= ~FLAG_REFRESH_DCFTIME;

		/* copy the DCF77 evaluated time to the current time and force display refresh */
		dtCurrentDateTime.SetHour(dtDcfData.GetHour());
		dtCurrentDateTime.SetMinute(dtDcfData.GetMinute());

		dtCurrentDateTime.SetDay(dtDcfData.GetDay());
		dtCurrentDateTime.SetDayOfWeek(dtDcfData.GetDayOfWeek());
		dtCurrentDateTime.SetMonth(dtDcfData.GetMonth());
		dtCurrentDateTime.SetYear(dtDcfData.GetYear());

		/* TODO: control second here or in ISR? */

		nFlags |= FLAG_REFRESH_DISPLAY;

	}
}

void DoButtonHandling() {

	/* check for menu */
	if(ButtonPressed(&PIN_BTN1, BUTTON_MENU) && bMenuStartAllowed) {
		bMenuStartAllowed = false;

		lmLCDMenu->RunMenu();

		lcDisplay->ClearLCDisplay();
		lcDisplay->CursorHome();

		nFlags |= FLAG_REFRESH_DISPLAY;
	}
}

void DoDisplayRefresh() {

	/* refresh the display */
	if((nFlags & FLAG_REFRESH_DISPLAY) > 0) {

		lcDisplay->CurserPos(0, 1);
		lcDisplay->WriteString(dtCurrentDateTime.GetDatestring(true));
		lcDisplay->CurserPos(0, 2);
		lcDisplay->WriteString(dtCurrentDateTime.GetTimestring(true));

		lcDisplay->CurserPos(13, 2);

		if((nFlags & FLAG_DO_ALARM) > 0) {
			lcDisplay->WriteData(LCD_GC_CHAR3);
		} else {
			lcDisplay->WriteString(" ");
		}

		lcDisplay->CurserPos(15, 2);

		if ((nFlags & FLAG_DO_DCF_RECV) == 0) {
			lcDisplay->WriteData(LCD_GC_CHAR2);
		}
		else if((nFlags & FLAG_UPDATE_DCF_DOT) > 0) {

			if((nFlags & FLAG_DCFSYMBOL_VISIBLE) > 0) {
				nFlags &= ~FLAG_DCFSYMBOL_VISIBLE;
				lcDisplay->WriteData(LCD_GC_CHAR0);
			} else {
				nFlags |= FLAG_DCFSYMBOL_VISIBLE;
				lcDisplay->WriteData(LCD_GC_CHAR1);
			}

			nFlags &= ~FLAG_UPDATE_DCF_DOT;
		}

		nFlags &= ~FLAG_REFRESH_DISPLAY;
	}
}

void DoAlarmHandling() {

	/* check if handling needs to be done */
	if((nFlags & FLAG_DO_ALARM) > 0) {
		/* check if alarm is already active */
		if((nFlags & FLAG_ALARM_ACTIVE) > 0) {
			/* TODO: alarm sound handling */
		} else {
			uint32_t nDiff = dtCurrentDateTime.GetTimeDifferenceInSecs((DateTime*)&tmAlarmTime);

			/* alarm is not active, check if it's active and light needs to be manipulated */
			if(nDiff == 0) {
				/* switch alarm on */
				nFlags |= FLAG_ALARM_ACTIVE;
			} else if(nDiff <= 900){
				/* be sure to switch on PWM and set correct OCR1A */
				if(OCR1A != GetDayLightDutyCycle(nDiff)) {
					OCR1A = GetDayLightDutyCycle(nDiff);
				}

				TCCR1A |= (1 << COM1A1);
			}
		}


	} else {
		/* just to be sure, switch off day light and sound */
		OCR1A = 0;
		OCR1B = 0;

		/* switch off both pwm signals */
		TCCR1A &= ~((1 << COM1A1) | (1 << COM1B1));
	}
}

uint16_t GetDayLightDutyCycle(uint32_t nDifferenceInSecs) {

	static uint16_t nLinearIndex = 0;
	static uint16_t nRet = 0;

	/* reset index if we started dimming phase */
	if(nDifferenceInSecs == 900) {
		nLinearIndex = 0;
	}

	if(nLinearIndex < 153) {

		/* we are in the linear dimming area, so take directly from lookup table */
		if(nLinearMapping[nLinearIndex] == nDifferenceInSecs) {
			/* if the current lookup table value doesn't match the current distance, the next one will */
			++nLinearIndex;
		}

		nRet = nLinearIndex - 1;
	} else {

		/* if we are out of the linear mode, the difference is used as lookup array index */
		if(nDifferenceInSecs <= 299) {
			nRet = nExpMapping[299 - nDifferenceInSecs];
		}

		/* static variable, if no condition matches, take last value */
	}

	return nRet;
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
	nFlags |= FLAG_UPDATE_DCF_DOT;

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
	TCCR1A = (1<<WGM10) | (1 << WGM11)| (1<<COM1A1) | (1<<COM1B1);
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
