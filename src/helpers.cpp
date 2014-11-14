/*
 * helpers.cpp
 *
 *  Created on: 09.11.2014
 *      Author: heiko
 */

#include "helpers.h"

void * operator new (size_t size) {
	return malloc(size);
}

void operator delete(void * ptr) {
	free(ptr);
}

bool ButtonPressed(volatile uint8_t *port, uint8_t pin) {


	if(!(*port & (1 << pin))) {

		_delay_ms(100);

		if(!(*port & (1 << pin))) {
			return true;
		}
	}

	return false;
}
