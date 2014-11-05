/*
 * DcfData.cpp
 *
 *  Created on: 26.10.2014
 *      Author: heiko
 */

#include "DcfData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DcfData::DcfData() {
	this->oDcfData_.nDcfData = 0;
}

DcfData::~DcfData() {
	// TODO Auto-generated destructor stub
}

void DcfData::Reset() volatile {
	DcfData();
}

void DcfData::AddBit(uint8_t nBitNo, uint8_t nBitVal) volatile {

	if (nBitNo <= 63) {
		if(nBitVal > 0) {
			this->oDcfData_.nDcfData |= (((uint64_t)1) << nBitNo);
		} else {
			this->oDcfData_.nDcfData &= ~(((uint64_t)1) << nBitNo);
		}
	}
}

bool DcfData::EvaluateDateTime(bool bWithReset) volatile {

	bool bParityOk = true;

	if(		!CheckParity((uint32_t)(this->oDcfData_.oDcfTimeInfo.nMinuteLow) | (this->oDcfData_.oDcfTimeInfo.nMinuteHigh << 4), this->oDcfData_.oDcfTimeInfo.nMinParity, false)
		||	!CheckParity((uint32_t)(this->oDcfData_.oDcfTimeInfo.nHourLow) | (this->oDcfData_.oDcfTimeInfo.nHourHigh << 4), this->oDcfData_.oDcfTimeInfo.nHourParity, false)) {
		bParityOk = false;
	}

/* TODO: fix/debug
 	if(!CheckParity((uint32_t)((((uint32_t)this->oDcfData_.oDcfTimeInfo.nCalDayLow))
			| 	(((uint32_t)this->oDcfData_.oDcfTimeInfo.nCalDayHigh) << 4)
			|	(((uint32_t)this->oDcfData_.oDcfTimeInfo.nWeekDay) << 6)
			|	(((uint32_t)this->oDcfData_.oDcfTimeInfo.nMonthLow) << 9)
			|	(((uint32_t)this->oDcfData_.oDcfTimeInfo.nMinuteHigh) << 13)
			|	(((uint32_t)this->oDcfData_.oDcfTimeInfo.nYearLow) << 14)
			|	(((uint32_t)this->oDcfData_.oDcfTimeInfo.nYearHigh) << 18)), this->oDcfData_.oDcfTimeInfo.nDateParity, false)) {
		bParityOk = false;
	}
*/

	if(bParityOk == true) {

		/* evaluate minute */
		this->tmTime_.nMinute = this->oDcfData_.oDcfTimeInfo.nMinuteLow + this->oDcfData_.oDcfTimeInfo.nMinuteHigh * 10;

		/* evaluate hour */
		this->tmTime_.nHour = this->oDcfData_.oDcfTimeInfo.nHourLow + this->oDcfData_.oDcfTimeInfo.nHourHigh * 10;

		/* evaluate day of week */
		this->dtDate_.nDayOfWeek = this->oDcfData_.oDcfTimeInfo.nWeekDay;

		/* evaluate day */
		this->dtDate_.nDay = this->oDcfData_.oDcfTimeInfo.nCalDayLow + this->oDcfData_.oDcfTimeInfo.nCalDayHigh * 10;

		/* evaluate month */
		this->dtDate_.nMonth = this->oDcfData_.oDcfTimeInfo.nMonthLow + this->oDcfData_.oDcfTimeInfo.nMonthHigh * 10;

		/* evaluate year */
		this->dtDate_.nYear = 2000 + this->oDcfData_.oDcfTimeInfo.nYearLow + this->oDcfData_.oDcfTimeInfo.nYearHigh * 10;
	}

	if(bWithReset)
		this->oDcfData_.nDcfData = 0;

	return bParityOk;
}

bool DcfData::CheckParity(uint32_t nData, uint8_t nParity, bool bOdd) volatile {

	for(int i = 0; i < 32; i++) {
		nParity ^= ((nData >> i) & 0x1);
	}

	if(bOdd) {
		return (nParity ^ 0);
	} else {
		return (nParity ^ 0x1);
	}
}
