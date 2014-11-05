/*
 * DcfData.h
 *
 *  Created on: 26.10.2014
 *      Author: heiko
 */

#ifndef SRC_DcfData_H_
#define SRC_DcfData_H_

#include <inttypes.h>
#include "DateTime.h"


/**
 * This is a class for representing and decoding DCF77 time data
 */
class DcfData : public DateTime {
private:
	union DCF77Data_t {
		uint64_t nDcfData;

		struct DCFTimeInfo_t {
			uint8_t nMinuteStart : 1;
			uint16_t nWeatherInfo : 14;
			uint8_t nCallBit : 1;
			uint8_t nTimeChange : 1;
			uint8_t nMEZ : 1;
			uint8_t nMESZ : 1;
			uint8_t nCorrection : 1;
			uint8_t nStartTimeInfo : 1;
			uint8_t nMinuteLow : 4;
			uint8_t nMinuteHigh : 3;
			uint8_t nMinParity : 1;
			uint8_t nHourLow : 4;
			uint8_t nHourHigh : 2;
			uint8_t nHourParity : 1;
			uint8_t nCalDayLow : 4;
			uint8_t nCalDayHigh : 2;
			uint8_t nWeekDay : 3;
			uint8_t nMonthLow : 4;
			uint8_t nMonthHigh : 1;
			uint8_t nYearLow : 4;
			uint8_t nYearHigh : 4;
			uint8_t nDateParity : 1;
			uint8_t nPadding : 5;
		} oDcfTimeInfo;
	} oDcfData_;

public:
	DcfData();																/**< default constructor */
	virtual ~DcfData();														/**< default destructor */

	void AddBit(uint8_t nBitNo, uint8_t nBitVal) volatile;					/**< method for adding a new DCF77 bit value */
	void Reset() volatile;													/**< method for resetting */
	bool EvaluateDateTime(bool bWithReset) volatile;						/**< method for evaluating the DCF77 time from DCF77 data */
	bool CheckParity(uint32_t nData, uint8_t nParity, bool bEven) volatile;	/**< method for checking for DCF77 even parity */
};

#endif /* SRC_DcfData_H_ */
