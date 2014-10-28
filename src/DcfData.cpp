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
	this->m_nDcfData = 0;
}

DcfData::~DcfData() {
	// TODO Auto-generated destructor stub
}

void DcfData::Reset() volatile {
	DcfData();
}

void DcfData::AddBit(uint8_t nBitNo, uint8_t nBitVal) volatile {

	if(nBitVal > 0) {
		this->m_nDcfData |= (1 << nBitNo);
	} else {
		this->m_nDcfData &= ~(1 << nBitNo);
	}
}

bool DcfData::EvaluateTime(bool bWithReset) volatile {

	/* TODO: parity checks */

	/* evaluate minute */
	this->m_tmTime.nMinute = ((this->m_nDcfData >> MINUTE_LOW_POS) & MINUTE_LOW_MASK) + ((this->m_nDcfData >> MINUTE_HIGH_POS) & MINUTE_HIGH_MASK) * 10;

	/* evaluate hour */
	this->m_tmTime.nHour = ((this->m_nDcfData >> HOUR_LOW_POS) & HOUR_LOW_MASK) + ((this->m_nDcfData >> HOUR_HIGH_POS) & HOUR_HIGH_MASK) * 10;

	/* evaluate day of week */
	this->m_dtDate.nDayOfWeek = ((this->m_nDcfData >> DAY_OF_WEEK_POS) & DAY_OF_WEEK_MASK);

	/* evaluate day */
	this->m_dtDate.nDay = ((this->m_nDcfData >> CALENDAR_DAY_LOW_POS) & CALENDAS_DAY_LOW_MASK) + ((this->m_nDcfData >> CALENDAR_DAY_HIGH_POS) & CALENDAR_DAY_HIGH_MASK) * 10;

	/* evaluate month */
	this->m_dtDate.nMonth = ((this->m_nDcfData >> MONTH_LOW_POS) & MONTH_LOW_MASK) + ((this->m_nDcfData >> MONTH_HIGH_POS) & MONTH_HIGH_MASK) * 10;

	/* evaluate year */
	this->m_dtDate.nYear = 2000 + ((this->m_nDcfData >> YEAR_LOW_POS) & YEAR_LOW_MASK) + ((this->m_nDcfData >> YEAR_HIGH_POS) & YEAR_HIGH_MASK) * 10;

	if(bWithReset)
		this->m_nDcfData = 0;

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
