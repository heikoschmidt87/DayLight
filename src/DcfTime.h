/*
 * DcfTime.h
 *
 *  Created on: 26.10.2014
 *      Author: heiko
 */

#ifndef SRC_DCFTIME_H_
#define SRC_DCFTIME_H_

#include <inttypes.h>
#include "Time.h"

/**
 * This is a class for representing and decoding DCF77 time data
 */
typedef struct {
	uint64_t nMinuteStart : 1;
	uint64_t nWeatherInfo : 14;
	uint64_t nCallBit : 1;
	uint64_t nTimeChange : 1;
	uint64_t nMEZ : 1;
	uint64_t nMESZ : 1;
	uint64_t nCorrection : 1;
	uint64_t nStartTimeInfo : 1;
	uint64_t nMinute : 7;
	uint64_t nMinParity : 1;
	uint64_t nHour : 6;
	uint64_t nHourParity : 1;
	uint64_t nCalDay : 6;
	uint64_t nWeekDay : 3;
	uint64_t nMonth : 5;
	uint64_t nYear : 8;
	uint64_t nDateParity : 1;
	uint64_t nRest : 5;
} DCFTimeInfo_t;

class DcfTime: public Time {
private:
	uint64_t m_nDcfData;

public:
	DcfTime();											/**< default constructor */
	virtual ~DcfTime();									/**< default destructor */

	void AddBit(uint8_t nBitNo, uint8_t nBitVal);		/**< method for adding a new DCF77 bit value */
	void Reset();										/**< method for resetting */
	bool EvaluateTime(bool bWithReset);					/**< method for evaluating the DCF77 time from DCF77 data */
};

#endif /* SRC_DCFTIME_H_ */
