/*
 * Date.h
 *
 *  Created on: 23.10.2014
 *      Author: heiko
 */

#ifndef SRC_DATE_H_
#define SRC_DATE_H_

/*
 * INCLUDES
 */
#include "system.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * STRUCTS
 */
const char *sDays[] = {"Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"};

/**
 * This is a class for representing date
 */
class Date {
private:
	uint8_t m_nDayOfWeek;	/**< uint8_t value, representing current day of the week */
	uint8_t m_nDay;			/**< uint8_t value, representing current day */
	uint8_t m_nMonth;		/**< uint8_t value, representing current month */
	uint16_t m_nYear;		/**< uint16_t value, representing current year */

public:
	Date();																	/**< default constructor */
	Date(uint8_t nDayOfWeek, uint8_t nDay, uint8_t nMonth, uint16_t nYear);	/**< constructor with variable initialization */
	virtual ~Date();														/**< default destructor */

	void Increase();														/**< increases date by one day */

	void SetDayOfWeek(uint8_t nDayOfWeek);									/**< setter-method for day of week */
	void SetDay(uint8_t nDay);												/**< setter-method for day */
	void SetMonth(uint8_t nMonth);											/**< setter-method for month */
	void SetYear(uint16_t nYear);											/**< setter-method for year */

	uint8_t GetDayOfWeek();													/**< getter-method for day of week */
	uint8_t GetDay();														/**< getter-method for day */
	uint8_t GetMonth();														/**< getter-method for month */
	uint16_t GetYear();														/**< getter-method for year */

	void GetDatestring(bool bWithYear, char* sString);						/**< getter for formatted date */

	bool bIsEqualTo(Date* oDate, bool bWithDayOfWeek);						/**< check method for testing if dates are equal */
};

#endif /* SRC_DATE_H_ */
