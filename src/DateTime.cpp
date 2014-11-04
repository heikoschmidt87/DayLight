/*
 * Time.cpp
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "DateTime.h"

DateTime::DateTime() {
	this->m_tmTime.nHour = 0;
	this->m_tmTime.nMinute = 0;
	this->m_tmTime.nSecond = 0;

	this->m_dtDate.nDayOfWeek = 1;
	this->m_dtDate.nDay = 1;
	this->m_dtDate.nMonth = 1;
	this->m_dtDate.nYear = 1979;
}

DateTime::DateTime(Time_t tmTime, Date_t dtDate) {
	this->m_tmTime = tmTime;
	this->m_dtDate = dtDate;
}

DateTime::~DateTime() {
	// TODO Auto-generated destructor stub
}

void DateTime::Increase() volatile {
	if(++this->m_tmTime.nSecond == 60) {
		this->m_tmTime.nSecond = 0;

		if(++this->m_tmTime.nMinute == 60) {
			this->m_tmTime.nMinute = 0;

			if(++this->m_tmTime.nHour == 24) {
				this->m_tmTime.nHour = 0;
			}
		}
	}

	if(		(this->m_tmTime.nHour == 0)
		&&	(this->m_tmTime.nMinute == 0)
		&&	(this->m_tmTime.nSecond == 0)) {

		uint8_t nDayCount = 0;

		switch(this->m_dtDate.nMonth) {
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				nDayCount = 31;
				break;

			case 4: case 6: case 9: case 11:
				nDayCount = 30;
				break;

			case 2:
				if(		((this->m_dtDate.nYear % 4 == 0)
					&&	(this->m_dtDate.nYear % 100 != 0))
					||	(this->m_dtDate.nYear % 400 == 0)) {
					nDayCount = 29;
				} else {
					nDayCount = 28;
				}
		}

		if(++this->m_dtDate.nDay > nDayCount) {

			this->m_dtDate.nDay = 0;

			if(++this->m_dtDate.nMonth > 12) {
					++this->m_dtDate.nYear;
					this->m_dtDate.nMonth = 1;
			}
		}

		if(++this->m_dtDate.nDayOfWeek > 6) {
			this->m_dtDate.nDayOfWeek = 0;
		}
	}
}

uint32_t DateTime::GetTimeDifferenceInSecs(DateTime *oTime) volatile {

	int16_t nHourDiffSecs = 0, nMinDiffSecs = 0, nSecDiffSecs = 0;

	if(this->m_tmTime.nHour <= oTime->GetHour())
		nHourDiffSecs = (oTime->GetHour() - this->m_tmTime.nHour) * 3600;
	else
		nHourDiffSecs = (24 - this->m_tmTime.nHour + oTime->GetHour()) + 3600;

	nMinDiffSecs = (oTime->GetMinute() - this->m_tmTime.nMinute) * 60;
	nSecDiffSecs = oTime->GetSecond() - this->m_tmTime.nSecond;

	return static_cast<uint32_t>(nHourDiffSecs + nMinDiffSecs + nSecDiffSecs);
}

void DateTime::SetSecond(uint8_t nSecond) volatile {
	this->m_tmTime.nSecond = nSecond;
}

void DateTime::SetMinute(uint8_t nMinute) volatile {
	this->m_tmTime.nMinute = nMinute;
}

void DateTime::SetHour(uint8_t nHour) volatile {
	this->m_tmTime.nHour = nHour;
}

uint8_t DateTime::GetSecond() volatile {
	return this->m_tmTime.nSecond;
}

uint8_t DateTime::GetMinute() volatile {
	return this->m_tmTime.nMinute;
}

uint8_t DateTime::GetHour() volatile {
	return this->m_tmTime.nHour;
}

char* DateTime::GetTimestring(bool bWithSecs) volatile {

	static char sString[17];

	if(bWithSecs) {
			sprintf(sString, "%.2lu:%.2lu:%.2lu", this->m_tmTime.nHour, this->m_tmTime.nMinute, this->m_tmTime.nSecond);
	}
	else {
			sprintf(sString, "%.2lu:%.2lu", this->m_tmTime.nHour, this->m_tmTime.nMinute);
	}

	return sString;
}

bool DateTime::IsTimeEqualTo(DateTime* oTime) volatile {
	return		(this->m_tmTime.nHour == oTime->GetHour())
			&&	(this->m_tmTime.nMinute == oTime->GetMinute())
			&&	(this->m_tmTime.nSecond == oTime->GetSecond());
}

void DateTime::SetDayOfWeek(uint8_t nDayOfWeek) volatile {
	this->m_dtDate.nDayOfWeek = nDayOfWeek;
}

void DateTime::SetDay(uint8_t nDay) volatile {
	this->m_dtDate.nDay = nDay;
}

void DateTime::SetMonth(uint8_t nMonth) volatile {
	this->m_dtDate.nMonth = nMonth;
}

void DateTime::SetYear(uint16_t nYear) volatile {
	this->m_dtDate.nYear = nYear;
}

uint8_t DateTime::GetDayOfWeek() volatile {
	return this->m_dtDate.nDayOfWeek;
}

uint8_t DateTime::GetDay() volatile {
	return this->m_dtDate.nDay;
}

uint8_t DateTime::GetMonth() volatile {
	return this->m_dtDate.nMonth;
}

uint16_t DateTime::GetYear() volatile {
	return this->m_dtDate.nYear;
}

char* DateTime::GetDatestring(bool bWithYear) volatile {
	static char sString[17];

	const char *sDays[] = {"Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"};

	if(bWithYear) {
		sprintf(sString, "%s - %02lu.%02lu.%04lu", sDays[this->m_dtDate.nDayOfWeek - 1], this->m_dtDate.nDay, this->m_dtDate.nMonth, this->m_dtDate.nYear);
	} else {
		sprintf(sString, "%s - %02lu.%02lu", sDays[this->m_dtDate.nDayOfWeek - 1], this->m_dtDate.nDay, this->m_dtDate.nMonth);
	}

	return sString;
}

bool DateTime::IsDateEqualTo(DateTime* oDate, bool bWithDayOfWeek) volatile {
	return 		this->m_dtDate.nDay == oDate->GetDay()
			&&	this->m_dtDate.nMonth == oDate->GetMonth()
			&&	this->m_dtDate.nYear == oDate->GetYear()
			&&	(bWithDayOfWeek && this->m_dtDate.nDayOfWeek == oDate->GetDayOfWeek());
}

