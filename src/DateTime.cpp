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
	this->tmTime_.nHour = 0;
	this->tmTime_.nMinute = 0;
	this->tmTime_.nSecond = 0;

	this->dtDate_.nDayOfWeek = 1;
	this->dtDate_.nDay = 1;
	this->dtDate_.nMonth = 1;
	this->dtDate_.nYear = 1979;
}

DateTime::DateTime(Time_t tmTime, Date_t dtDate) {
	this->tmTime_ = tmTime;
	this->dtDate_ = dtDate;
}

DateTime::~DateTime() {
	// TODO Auto-generated destructor stub
}

void DateTime::Increase() volatile {
	if(++this->tmTime_.nSecond == 60) {
		this->tmTime_.nSecond = 0;

		if(++this->tmTime_.nMinute == 60) {
			this->tmTime_.nMinute = 0;

			if(++this->tmTime_.nHour == 24) {
				this->tmTime_.nHour = 0;
			}
		}
	}

	if(		(this->tmTime_.nHour == 0)
		&&	(this->tmTime_.nMinute == 0)
		&&	(this->tmTime_.nSecond == 0)) {

		uint8_t nDayCount = 0;

		switch(this->dtDate_.nMonth) {
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				nDayCount = 31;
				break;

			case 4: case 6: case 9: case 11:
				nDayCount = 30;
				break;

			case 2:
				if(		((this->dtDate_.nYear % 4 == 0)
					&&	(this->dtDate_.nYear % 100 != 0))
					||	(this->dtDate_.nYear % 400 == 0)) {
					nDayCount = 29;
				} else {
					nDayCount = 28;
				}
		}

		if(++this->dtDate_.nDay > nDayCount) {

			this->dtDate_.nDay = 0;

			if(++this->dtDate_.nMonth > 12) {
					++this->dtDate_.nYear;
					this->dtDate_.nMonth = 1;
			}
		}

		if(++this->dtDate_.nDayOfWeek > 6) {
			this->dtDate_.nDayOfWeek = 0;
		}
	}
}

uint32_t DateTime::GetTimeDifferenceInSecs(DateTime *oTime) volatile {

	int16_t nHourDiffSecs = 0, nMinDiffSecs = 0, nSecDiffSecs = 0;

	if(this->tmTime_.nHour <= oTime->GetHour())
		nHourDiffSecs = (oTime->GetHour() - this->tmTime_.nHour) * 3600;
	else
		nHourDiffSecs = (24 - this->tmTime_.nHour + oTime->GetHour()) + 3600;

	nMinDiffSecs = (oTime->GetMinute() - this->tmTime_.nMinute) * 60;
	nSecDiffSecs = oTime->GetSecond() - this->tmTime_.nSecond;

	return static_cast<uint32_t>(nHourDiffSecs + nMinDiffSecs + nSecDiffSecs);
}

void DateTime::SetSecond(uint8_t nSecond) volatile {
	this->tmTime_.nSecond = nSecond;
}

void DateTime::SetMinute(uint8_t nMinute) volatile {
	this->tmTime_.nMinute = nMinute;
}

void DateTime::SetHour(uint8_t nHour) volatile {
	this->tmTime_.nHour = nHour;
}

uint8_t DateTime::GetSecond() volatile {
	return this->tmTime_.nSecond;
}

uint8_t DateTime::GetMinute() volatile {
	return this->tmTime_.nMinute;
}

uint8_t DateTime::GetHour() volatile {
	return this->tmTime_.nHour;
}

char* DateTime::GetTimestring(bool bWithSecs) volatile {

	static char sString[17];

	if(bWithSecs) {
			sprintf(sString, "%.2lu:%.2lu:%.2lu", this->tmTime_.nHour, this->tmTime_.nMinute, this->tmTime_.nSecond);
	}
	else {
			sprintf(sString, "%.2lu:%.2lu", this->tmTime_.nHour, this->tmTime_.nMinute);
	}

	return sString;
}

bool DateTime::IsTimeEqualTo(DateTime* oTime) volatile {
	return		(this->tmTime_.nHour == oTime->GetHour())
			&&	(this->tmTime_.nMinute == oTime->GetMinute())
			&&	(this->tmTime_.nSecond == oTime->GetSecond());
}

void DateTime::SetDayOfWeek(uint8_t nDayOfWeek) volatile {
	this->dtDate_.nDayOfWeek = nDayOfWeek;
}

void DateTime::SetDay(uint8_t nDay) volatile {
	this->dtDate_.nDay = nDay;
}

void DateTime::SetMonth(uint8_t nMonth) volatile {
	this->dtDate_.nMonth = nMonth;
}

void DateTime::SetYear(uint16_t nYear) volatile {
	this->dtDate_.nYear = nYear;
}

uint8_t DateTime::GetDayOfWeek() volatile {
	return this->dtDate_.nDayOfWeek;
}

uint8_t DateTime::GetDay() volatile {
	return this->dtDate_.nDay;
}

uint8_t DateTime::GetMonth() volatile {
	return this->dtDate_.nMonth;
}

uint16_t DateTime::GetYear() volatile {
	return this->dtDate_.nYear;
}

char* DateTime::GetDatestring(bool bWithYear) volatile {
	static char sString[17];

	const char *sDays[] = {"Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"};

	if(bWithYear) {
		sprintf(sString, "%s - %02lu.%02lu.%04lu", sDays[this->dtDate_.nDayOfWeek - 1], this->dtDate_.nDay, this->dtDate_.nMonth, this->dtDate_.nYear);
	} else {
		sprintf(sString, "%s - %02lu.%02lu", sDays[this->dtDate_.nDayOfWeek - 1], this->dtDate_.nDay, this->dtDate_.nMonth);
	}

	return sString;
}

bool DateTime::IsDateEqualTo(DateTime* oDate, bool bWithDayOfWeek) volatile {
	return 		this->dtDate_.nDay == oDate->GetDay()
			&&	this->dtDate_.nMonth == oDate->GetMonth()
			&&	this->dtDate_.nYear == oDate->GetYear()
			&&	(bWithDayOfWeek && this->dtDate_.nDayOfWeek == oDate->GetDayOfWeek());
}

