/*
 * Time.cpp
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Time.h"


Time::Time() {
	this->m_tmTime.nHour = 0;
	this->m_tmTime.nMinute = 0;
	this->m_tmTime.nSecond = 0;
}

Time::Time(Time_t tmTime) {
	this->m_tmTime = tmTime;
}

Time::~Time() {
	// TODO Auto-generated destructor stub
}

void Time::Increase() volatile {
	if(++this->m_tmTime.nSecond == 60) {
		this->m_tmTime.nSecond = 0;

		if(++this->m_tmTime.nMinute == 60) {
			this->m_tmTime.nMinute = 0;

			if(++this->m_tmTime.nHour == 24) {
				this->m_tmTime.nHour = 0;
			}
		}
	}
}

uint32_t Time::GetDifferenceInSecs(Time *oTime) volatile {

	int16_t nHourDiffSecs = 0, nMinDiffSecs = 0, nSecDiffSecs = 0;

	if(this->m_tmTime.nHour <= oTime->GetHour())
		nHourDiffSecs = (oTime->GetHour() - this->m_tmTime.nHour) * 3600;
	else
		nHourDiffSecs = (24 - this->m_tmTime.nHour + oTime->GetHour()) + 3600;

	nMinDiffSecs = (oTime->GetMinute() - this->m_tmTime.nMinute) * 60;
	nSecDiffSecs = oTime->GetSecond() - this->m_tmTime.nSecond;

	return static_cast<uint32_t>(nHourDiffSecs + nMinDiffSecs + nSecDiffSecs);
}

void Time::SetSecond(uint8_t nSecond) volatile {
	this->m_tmTime.nSecond = nSecond;
}

void Time::SetMinute(uint8_t nMinute) volatile {
	this->m_tmTime.nMinute = nMinute;
}

void Time::SetHour(uint8_t nHour) volatile {
	this->m_tmTime.nHour = nHour;
}

uint8_t Time::GetSecond() volatile {
	return this->m_tmTime.nSecond;
}

uint8_t Time::GetMinute() volatile {
	return this->m_tmTime.nMinute;
}

uint8_t Time::GetHour() volatile {
	return this->m_tmTime.nHour;
}

char* Time::GetTimestring(bool bWithSecs) volatile {

	static char sString[17];

	if(bWithSecs) {
			sprintf(sString, "%.2lu:%.2lu:%.2lu", this->m_tmTime.nHour, this->m_tmTime.nMinute, this->m_tmTime.nSecond);
	}
	else {
			sprintf(sString, "%.2lu:%.2lu", this->m_tmTime.nHour, this->m_tmTime.nMinute);
	}

	return sString;
}

bool Time::IsEqualTo(Time* oTime) volatile {
	return		(this->m_tmTime.nHour == oTime->GetHour())
			&&	(this->m_tmTime.nMinute == oTime->GetMinute())
			&&	(this->m_tmTime.nSecond == oTime->GetSecond());
}
