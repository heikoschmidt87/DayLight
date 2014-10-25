/*
 * Date.cpp
 *
 *  Created on: 23.10.2014
 *      Author: heiko
 */

#include "Date.h"

static const char *sDays[] = {"Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"};

Date::Date() {
	this->m_dtDate.nDayOfWeek = 1;
	this->m_dtDate.nDay = 1;
	this->m_dtDate.nMonth = 1;
	this->m_dtDate.nYear = 1979;
}

Date::Date(Date_t dtDate) {
	this->m_dtDate = dtDate;
}

Date::~Date() {
	// TODO Auto-generated destructor stub
}

void Date::SetDayOfWeek(uint8_t nDayOfWeek) {
	this->m_dtDate.nDayOfWeek = nDayOfWeek;
}

void Date::SetDay(uint8_t nDay) {
	this->m_dtDate.nDay = nDay;
}

void Date::SetMonth(uint8_t nMonth) {
	this->m_dtDate.nMonth = nMonth;
}

void Date::SetYear(uint16_t nYear) {
	this->m_dtDate.nYear = nYear;
}

uint8_t Date::GetDayOfWeek() {
	return this->m_dtDate.nDayOfWeek;
}

uint8_t Date::GetDay() {
	return this->m_dtDate.nDay;
}

uint8_t Date::GetMonth() {
	return this->m_dtDate.nMonth;
}

uint16_t Date::GetYear() {
	return this->m_dtDate.nYear;
}

void Date::Increase() {

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

char* Date::GetDatestring(bool bWithYear) {
	static char sString[17];

	if(bWithYear) {
		sprintf(sString, "%s - %02d.%02d", sDays[this->m_dtDate.nDayOfWeek - 1], this->m_dtDate.nDay, this->m_dtDate.nMonth);
	} else {
		sprintf(sString, "%s - %02d.%02d.%04d", sDays[this->m_dtDate.nDayOfWeek - 1], this->m_dtDate.nDay, this->m_dtDate.nMonth, this->m_dtDate.nYear);
	}

	return sString;
}

bool Date::bIsEqualTo(Date* oDate, bool bWithDayOfWeek) {
	return 		this->m_dtDate.nDay == oDate->GetDay()
			&&	this->m_dtDate.nMonth == oDate->GetMonth()
			&&	this->m_dtDate.nYear == oDate->GetYear()
			&&	(bWithDayOfWeek && this->m_dtDate.nDayOfWeek == oDate->GetDayOfWeek());
}
