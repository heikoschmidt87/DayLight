/*
 * DcfTime.cpp
 *
 *  Created on: 26.10.2014
 *      Author: heiko
 */

#include "DcfTime.h"

DcfTime::DcfTime() {
	this->m_nDcfData = 0;

}

DcfTime::~DcfTime() {
	// TODO Auto-generated destructor stub
}

void DcfTime::Reset() {
	DcfTime();
}

void DcfTime::AddBit(uint8_t nBitNo, uint8_t nBitVal) {

	if(nBitVal > 0) {
		this->m_nDcfData |= (1 << nBitNo);
	} else {
		this->m_nDcfData &= ~(1 << nBitNo);
	}
}

bool DcfTime::EvaluateTime(bool bWithReset) {
	return false;
}
