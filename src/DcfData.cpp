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
	this->m_oDcfData.nDcfData = 0;
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
			this->m_oDcfData.nDcfData |= (((uint64_t)1) << nBitNo);
		} else {
			this->m_oDcfData.nDcfData &= ~(((uint64_t)1) << nBitNo);
		}
	}
}

bool DcfData::EvaluateDateTime(bool bWithReset) volatile {

	/* TODO: parity checks */

	/* evaluate minute */
	this->m_tmTime.nMinute = this->m_oDcfData.oDcfTimeInfo.nMinuteLow + this->m_oDcfData.oDcfTimeInfo.nMinuteHigh * 10;

	/* evaluate hour */
	this->m_tmTime.nHour = this->m_oDcfData.oDcfTimeInfo.nHourLow + this->m_oDcfData.oDcfTimeInfo.nHourHigh * 10;

	/* evaluate day of week */
	this->m_dtDate.nDayOfWeek = this->m_oDcfData.oDcfTimeInfo.nWeekDay;

	/* evaluate day */
	this->m_dtDate.nDay = this->m_oDcfData.oDcfTimeInfo.nCalDayLow + this->m_oDcfData.oDcfTimeInfo.nCalDayHigh * 10;

	/* evaluate month */
	this->m_dtDate.nMonth = this->m_oDcfData.oDcfTimeInfo.nMonthLow + this->m_oDcfData.oDcfTimeInfo.nMonthHigh * 10;

	/* evaluate year */
	this->m_dtDate.nYear = 2000 + this->m_oDcfData.oDcfTimeInfo.nYearLow + this->m_oDcfData.oDcfTimeInfo.nYearHigh * 10;

	if(bWithReset)
		this->m_oDcfData.nDcfData = 0;

	return true /*false*/;
}

bool DcfData::CheckParity(uint16_t nData, uint8_t nParity) volatile {
	uint8_t nCounter = 0;
	uint8_t nMask = 0x01;

	for(int i = 0; i < 8; i++) {
		if(nData & (nMask << i)) {
			nCounter++;
		}
	}

	if((nCounter % 2) == 0) {
		return nParity == 0;
	} else {
		return nParity > 0;
	}
}

