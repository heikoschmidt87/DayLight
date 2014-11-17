/*
 * system.h
 *
 *  Created on: 30.09.2014
 *      Author: heiko
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_


////////////////////////////////////
// INCLUDES
////////////////////////////////////
#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "helpers.h"
#include "DateTime.h"
#include "DcfData.h"
#include "LCDisplay.h"
#include "LcdMenu.h"
#include "MenuEntry.h"

////////////////////////////////////
// ERRORS
////////////////////////////////////
typedef uint8_t Ret_Err_Def;

#define RET_OK		0x00
#define	RET_NOK		0x80

////////////////////////////////////
// Global Functions
////////////////////////////////////
extern void InitFlags();
extern void InitDayLightAlarm();

extern void Menu_SetTime();
extern void Menu_SetDate();
extern void Menu_SetAlarm();
extern void Menu_SwitchAlarm();
extern void Menu_SetSnoozeTime();
extern void Menu_SwitchDCF();

////////////////////////////////////
// STRUCTS
////////////////////////////////////
/*
TODO: Reserved for further use

struct {
	uint8_t bRefreshDisplay : 1;
	uint8_t bDcfFallingEdge : 1;
	uint8_t bDoAlarm : 1;
	uint8_t bSnooze : 1;
} oFlags;
*/

////////////////////////////////////
// DEFINES
////////////////////////////////////
#define BUTTON_SNOOZE	PC4
#define BUTTON_MENU		PC5
#define BUTTON_ADJUST	PC6
#define BUTTON_LIGHT	PC7
#define DAY_LIGHT		PD5
#define SPEAKER			PD4
#define DISPLAY_LIGHT	PB0

#define PORT_BTN1		PORTC
#define PORT_BTN2		PORTC
#define PORT_DAY_LIGHT	PORTD
#define PORT_SPEAKER	PORTD
#define PORT_DISPLIGHT	PORTB
#define PORT_LCD		PORTA

#define PIN_BTN1		PINC
#define PIN_BTN2		PINC

#define DDR_BTN1		DDRC
#define DDR_BTN2		DDRC
#define DDR_DAY_LIGHT	DDRD
#define DDR_SPEAKER		DDRD
#define DDR_DISPLIGHT	DDRB
#define DDR_LCD			DDRA

#define LCD_DB        	PA0
#define LCD_RS        	PA5
#define LCD_EN        	PA4

#define FLAG_REFRESH_DISPLAY	0x01
#define FLAG_DCF_FALLING_EDGE	0x02
#define FLAG_DO_ALARM			0x04
#define FLAG_SNOOZE				0x08
#define FLAG_DCFSYMBOL_VISIBLE	0x10
#define FLAG_REFRESH_DCFTIME	0x20
#define FLAG_UPDATE_DCF_DOT		0x40
#define FLAG_DO_DCF_RECV		0x80

#define NO_OF_MENU_ENTRIES		6

////////////////////////////////////
// GLOBALS
////////////////////////////////////
extern volatile DateTime dtCurrentDateTime;
extern volatile DateTime tmAlarmTime;
extern volatile DcfData dtDcfData;

extern volatile uint8_t nMenuSecondCounter;

extern volatile LCDisplay *lcDisplay;

extern volatile uint8_t nClockOverflows;
extern volatile uint16_t nFlags;

extern volatile uint64_t nBitSequenceTime;
extern volatile uint64_t nBitTime;
extern volatile uint8_t nLowLevelTicks;
extern volatile uint8_t nCurrentBitNumber;

/* menu structure
 * 1 - Uhr stellen
 * 2 - Datum stellen
 * 3 - Alarmzeit stellen
 * 4 - Alarm an-/ausschalten
 * 5 - Schlummerzeit
 * 6 - DCF an/aus
 * */
extern MenuEntry *meMenuEntries[NO_OF_MENU_ENTRIES];
extern LcdMenu *lmLCDMenu;


#endif /* SYSTEM_H_ */
