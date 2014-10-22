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
	this->m_nHour = 0;
	this->m_nMinute = 0;
	this->m_nSecond = 0;
}

Time::Time(uint8_t nHour, uint8_t nMinute, uint8_t nSecond) {
	this->m_nHour = nHour;
	this->m_nMinute = nMinute;
	this->m_nSecond = nSecond;
}

Time::~Time() {
	// TODO Auto-generated destructor stub
}

void Time::Increase() {
	if(++this->m_nSecond == 60) {
		this->m_nSecond = 0;

		if(++this->m_nMinute == 60) {
			this->m_nMinute = 0;

			if(++this->m_nHour == 24) {
				this->m_nHour = 0;
			}
		}
	}
}

uint32_t Time::GetDifferenceInSecs(Time *oTime) {

	int16_t nHourDiffSecs = 0, nMinDiffSecs = 0, nSecDiffSecs = 0;

	if(this->m_nHour <= oTime->GetHour())
		nHourDiffSecs = (oTime->GetHour() - this->m_nHour) * 3600;
	else
		nHourDiffSecs = (24 - this->m_nHour + oTime->GetHour()) + 3600;

	nMinDiffSecs = (oTime->GetMinute() - this->m_nMinute) * 60;
	nSecDiffSecs = oTime->GetSecond() - this->m_nSecond;

	return static_cast<uint32_t>(nHourDiffSecs + nMinDiffSecs + nSecDiffSecs);
}

void Time::SetSecond(uint8_t nSecond) {
	this->m_nSecond = nSecond;
}

void Time::SetMinute(uint8_t nMinute) {
	this->m_nMinute = nMinute;
}

void Time::SetHour(uint8_t nHour) {
	this->m_nHour = nHour;
}

uint8_t Time::GetSecond() {
	return this->m_nSecond;
}

uint8_t Time::GetMinute() {
	return this->m_nMinute;
}

uint8_t Time::GetHour() {
	return this->m_nHour;
}

void Time::GetTimestring(bool bWithSecs, char* sString) {

	if(bWithSecs) {
			sprintf(sString, "%.2d:%.2d:%.2d", this->m_nHour, this->m_nMinute, this->m_nSecond);
	}
	else {
			sprintf(sString, "%.2d:%.2d", this->m_nHour, this->m_nMinute);
	}
}

bool Time::IsEqualTo(Time* oTime) {
	return		(this->m_nHour == oTime->GetHour())
			&&	(this->m_nMinute == oTime->GetMinute())
			&&	(this->m_nSecond == oTime->GetSecond());
}
