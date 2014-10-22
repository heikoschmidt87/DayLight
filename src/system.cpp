/*
 * system.cpp
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#include "system.h"

void * operator new (size_t size) {
	return malloc(size);
}

void operator delete(void * ptr) {
	free(ptr);
}
