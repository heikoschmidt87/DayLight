/*
 * DcfData.h
 *
 *  Created on: 26.10.2014
 *      Author: heiko
 */

#ifndef SRC_DcfData_H_
#define SRC_DcfData_H_

#include <inttypes.h>
#include "Time.h"
#include "Date.h"

/**
 * This is a class for representing and decoding DCF77 time data
 */
class DcfData : public Time, public Date {
private:
	uint64_t m_nDcfData;

	/* TODO: check better solution with union */

	enum {
		MINUTE_START_POS = 0,
		MINUTE_START_MASK = 0x1,

		MINUTE_LOW_POS = 21,
		MINUTE_LOW_MASK = 0xF,

		MINUTE_HIGH_POS = 25,
		MINUTE_HIGH_MASK = 0x7,

		MINUTE_PARITY_POS = 28,
		MINUTE_PARITY_MASK = 0x1,

		HOUR_LOW_POS = 29,
		HOUR_LOW_MASK = 0xF,

		HOUR_HIGH_POS = 33,
		HOUR_HIGH_MASK = 0x3,

		HOUR_PARITY_POS = 35,
		HOUR_PARITY_MASK = 0x1,

		CALENDAR_DAY_LOW_POS = 36,
		CALENDAS_DAY_LOW_MASK = 0xF,

		CALENDAR_DAY_HIGH_POS = 40,
		CALENDAR_DAY_HIGH_MASK = 0x3,

		DAY_OF_WEEK_POS = 42,
		DAY_OF_WEEK_MASK = 0x7,

		MONTH_LOW_POS = 45,
		MONTH_LOW_MASK = 0xF,

		MONTH_HIGH_POS = 49,
		MONTH_HIGH_MASK = 0x1,

		YEAR_LOW_POS = 50,
		YEAR_LOW_MASK = 0xF,

		YEAR_HIGH_POS = 54,
		YEAR_HIGH_MASK = 0xF,

		DATE_PARITY_POS = 58,
		DATE_PARITY_MASK = 0x1
	};

public:
	DcfData();													/**< default constructor */
	virtual ~DcfData();											/**< default destructor */

	void AddBit(uint8_t nBitNo, uint8_t nBitVal) volatile;		/**< method for adding a new DCF77 bit value */
	void Reset() volatile;										/**< method for resetting */
	bool EvaluateTime(bool bWithReset) volatile;				/**< method for evaluating the DCF77 time from DCF77 data */
	bool CheckParity(uint16_t nData, uint8_t nParity) volatile;	/**< method for checking for DCF77 even parity */
};

#endif /* SRC_DcfData_H_ */
