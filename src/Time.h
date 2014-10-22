/*
 * Time.h
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#ifndef SRC_TIME_H_
#define SRC_TIME_H_

////////////////////////////////////
// INCLUDES
////////////////////////////////////
#include "system.h"

////////////////////////////////////
// CLASS
////////////////////////////////////

class Time {
private:
	uint8_t m_nHour;
	uint8_t m_nMinute;
	uint8_t m_nSecond;

public:
	Time();
	Time(uint8_t nHour, uint8_t nMinute, uint8_t nSecond);
	virtual ~Time();

	void Increase();

	void SetSecond(uint8_t nSecond);
	void SetMinute(uint8_t nMinute);
	void SetHour(uint8_t nHour);

	uint8_t GetSecond();
	uint8_t GetMinute();
	uint8_t GetHour();

	void GetTimestring(bool bWithSecs, char* sString);

	bool IsEqualTo(Time* oTime);

	uint32_t GetDifferenceInSecs(Time *oTime);
};

#endif /* SRC_TIME_H_ */
