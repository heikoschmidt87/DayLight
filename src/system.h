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

////////////////////////////////////
// STRUCTS
////////////////////////////////////
static struct {
	uint8_t bRefreshDisplay : 1;
	uint8_t bDcfFallingEdge : 1;
	uint8_t bDoAlarm : 1;
	uint8_t bSnooze : 1;
} oFlags;


#endif /* SYSTEM_H_ */
