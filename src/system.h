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
#include "Time.h"



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
static struct {
	uint8_t bRefreshDisplay : 1;
	uint8_t bDcfFallingEdge : 1;
	uint8_t bDoAlarm : 1;
	uint8_t bSnooze : 1;
} oFlags;

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

////////////////////////////////////
// GLOBALS
////////////////////////////////////
extern Time tmCurrentTime;
extern Time tmAlarmTime;
extern Date dtCurrentDate;

#endif /* SYSTEM_H_ */
