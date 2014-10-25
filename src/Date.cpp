/*
 * Date.cpp
 *
 *  Created on: 23.10.2014
 *      Author: heiko
 */

#include "Date.h"

static const char *sDays[] = {"Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"};

Date::Date() {
	this->m_nDayOfWeek = 1;
	this->m_nDay = 1;
	this->m_nMonth = 1;
	this->m_nYear = 1979;
}

Date::Date(uint8_t nDayOfWeek, uint8_t nDay, uint8_t nMonth, uint16_t nYear) {
	this->m_nDayOfWeek = nDayOfWeek;
	this->m_nDay = nDay;
	this->m_nMonth = nMonth;
	this->m_nYear = nYear;
}

Date::~Date() {
	// TODO Auto-generated destructor stub
}

void Date::SetDayOfWeek(uint8_t nDayOfWeek) {
	this->m_nDayOfWeek = nDayOfWeek;
}

void Date::SetDay(uint8_t nDay) {
	this->m_nDay = nDay;
}

void Date::SetMonth(uint8_t nMonth) {
	this->m_nMonth = nMonth;
}

void Date::SetYear(uint16_t nYear) {
	this->m_nYear = nYear;
}

uint8_t Date::GetDayOfWeek() {
	return this->m_nDayOfWeek;
}

uint8_t Date::GetDay() {
	return this->m_nDay;
}

uint8_t Date::GetMonth() {
	return this->m_nMonth;
}

uint16_t Date::GetYear() {
	return this->m_nYear;
}

void Date::Increase() {

	uint8_t nDayCount = 0;

	switch(this->m_nMonth) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			nDayCount = 31;
			break;

		case 4: case 6: case 9: case 11:
			nDayCount = 30;
			break;

		case 2:
			if(		((this->m_nYear % 4 == 0)
				&&	(this->m_nYear % 100 != 0))
				||	(this->m_nYear % 400 == 0)) {
				nDayCount = 29;
			} else {
				nDayCount = 28;
			}
	}

	if(++this->m_nDay > nDayCount) {

		this->m_nDay = 0;

		if(++this->m_nMonth > 12) {
				++this->m_nYear;
				this->m_nMonth = 1;
		}
	}
}

void Date::GetDatestring(bool bWithYear, char* sString) {
	if(bWithYear) {
		sprintf(sString, "%s - %02d.%02d", sDays[this->m_nDayOfWeek - 1], this->m_nDay, this->m_nMonth);
	} else {
		sprintf(sString, "%s - %02d.%02d.%04d", sDays[this->m_nDayOfWeek - 1], this->m_nDay, this->m_nMonth, this->m_nYear);;
	}
}

bool Date::bIsEqualTo(Date* oDate, bool bWithDayOfWeek) {
	return 		this->m_nDay == oDate->GetDay()
			&&	this->m_nMonth == oDate->GetMonth()
			&&	this->m_nYear == oDate->GetYear()
			&&	(bWithDayOfWeek && this->m_nDayOfWeek == oDate->GetDayOfWeek());
}
