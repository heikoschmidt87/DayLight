/*
 * Time.h
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#ifndef SRC_TIME_H_
#define SRC_TIME_H_

/*
 * INCLUDES
 */
#include "system.h"

/**
 * This is a class for representing time and enabling to compare times.
 */
class Time {
private:
	uint8_t m_nHour;		/**< uint8_t value, representing current hour value */
	uint8_t m_nMinute;		/**< uint8_t value, representing current minute value */
	uint8_t m_nSecond;		/**< uint8_t value, representing current second value */

public:
	Time();														/**< default constructor */
	Time(uint8_t nHour, uint8_t nMinute, uint8_t nSecond);		/**< constructor with variable initialization */
	virtual ~Time();											/**< default destructor */

	void Increase();											/**< increases time by one second */

	void SetSecond(uint8_t nSecond);							/**< setter-method for second */
	void SetMinute(uint8_t nMinute);							/**< setter-method for minute */
	void SetHour(uint8_t nHour);								/**< setter-method for hour */

	uint8_t GetSecond();										/**< getter-method for second */
	uint8_t GetMinute();										/**< getter-method for minute */
	uint8_t GetHour();											/**< getter-method for hour */

	void GetTimestring(bool bWithSecs, char* sString);			/**< getter for formatted timestring */

	bool IsEqualTo(Time* oTime);								/**< check method for testing if times are equal */

	uint32_t GetDifferenceInSecs(Time *oTime);					/**< calculates the difference between two times in seconds */
};

#endif /* SRC_TIME_H_ */
