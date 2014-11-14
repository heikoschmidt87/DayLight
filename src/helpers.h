/*
 * helpers.h
 *
 *  Created on: 09.11.2014
 *      Author: heiko
 */

#ifndef SRC_HELPERS_H_
#define SRC_HELPERS_H_


////////////////////////////////////
// INCLUDES
////////////////////////////////////
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>


////////////////////////////////////
// HELPERS
////////////////////////////////////
extern void * operator new(size_t size);
extern void operator delete(void * ptr);
extern bool ButtonPressed(volatile uint8_t *port, uint8_t pin);



#endif /* SRC_HELPERS_H_ */
