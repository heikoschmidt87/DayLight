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

#endif /* SYSTEM_H_ */
