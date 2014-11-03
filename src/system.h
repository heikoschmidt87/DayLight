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

#include "Date.h"
#include "DcfData.h"
#include "Time.h"
#include "lcd-routines.h"		/* TODO: own OO-implementation */



////////////////////////////////////
// ERRORS
////////////////////////////////////
typedef uint8_t Ret_Err_Def;

#define RET_OK		0x00
#define	RET_NOK		0x80

////////////////////////////////////
// HELPERS
////////////////////////////////////
void * operator new(size_t size);
void operator delete(void * ptr);

void InitFlags();
void InitDayLightAlarm();

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
#define BUTTON_SNOOZE	PD5
#define BUTTON_MENU		PD6
#define BUTTON_ADJUST	PD7
#define BUTTON_LIGHT	PB0
#define DAY_LIGHT		PB1
#define SPEAKER			PB2
#define DISPLAY_LIGHT	PD0

#define PORT_BTN1		PORTD
#define PORT_BTN2		PORTB
#define PORT_DAY_LIGHT	PORTB
#define PORT_SPEAKER	PORTB
#define PORT_DISPLIGHT	PORTD

#define PIN_BTN1		PIND
#define PIN_BTN2		PINB

#define DDR_BTN1		DDRD
#define DDR_BTN2		DDRB
#define DDR_DAY_LIGHT	DDRB
#define DDR_SPEAKER		DDRB
#define DDR_DISPLIGHT	DDRD

#define FLAG_REFRESH_DISPLAY	0x01
#define FLAG_DCF_FALLING_EDGE	0x02
#define FLAG_DO_ALARM			0x04
#define FLAG_SNOOZE				0x08
#define FLAG_DCFSYMBOL_VISIBLE	0x10
#define FLAG_REFRESH_DCFTIME	0x20
#define FLAG_UPDATE_DCF_DOT		0x40

////////////////////////////////////
// GLOBALS
////////////////////////////////////
extern volatile Time tmCurrentTime;
extern volatile Time tmAlarmTime;
extern volatile DcfData tmDcfData;
extern volatile Date dtCurrentDate;

extern volatile uint8_t nClockOverflows;
extern volatile uint8_t nFlags;

extern volatile uint64_t nBitSequenceTime;
extern volatile uint64_t nBitTime;
extern volatile uint8_t nLowLevelTicks;
extern volatile uint8_t nCurrentBitNumber;

#endif /* SYSTEM_H_ */
