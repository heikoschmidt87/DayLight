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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

/**
 * This is a class for representing date
 */
typedef struct {
	uint32_t nDayOfWeek : 3;
	uint32_t nDay : 5;
	uint32_t nMonth : 4;
	uint32_t nYear : 12;
} Date_t;

class Date {
private:
	static const char *sDays[7];

	Date_t m_dtDate;

public:
	Date();																	/**< default constructor */
	Date(Date_t dtDate);													/**< constructor with variable initialization */
	virtual ~Date();														/**< default destructor */

	void Increase() volatile;												/**< increases date by one day */

	void SetDayOfWeek(uint8_t nDayOfWeek) volatile;							/**< setter-method for day of week */
	void SetDay(uint8_t nDay) volatile;										/**< setter-method for day */
	void SetMonth(uint8_t nMonth) volatile;									/**< setter-method for month */
	void SetYear(uint16_t nYear) volatile;									/**< setter-method for year */

	uint8_t GetDayOfWeek() volatile;										/**< getter-method for day of week */
	uint8_t GetDay() volatile;												/**< getter-method for day */
	uint8_t GetMonth() volatile;											/**< getter-method for month */
	uint16_t GetYear() volatile;											/**< getter-method for year */

	char* GetDatestring(bool bWithYear) volatile;							/**< getter for formatted date */

	bool bIsEqualTo(Date* oDate, bool bWithDayOfWeek) volatile;				/**< check method for testing if dates are equal */

};

#endif /* SRC_DATE_H_ */
