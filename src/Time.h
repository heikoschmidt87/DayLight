/*
 * Time.h
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#ifndef SRC_TIME_H_
#define SRC_TIME_H_

/**
 * This is a class for representing time and enabling to compare times.
 */
typedef struct {
	uint32_t nHour : 5;
	uint32_t nMinute : 6;
	uint32_t nSecond : 6;
} Time_t;


class Time {
private:
	Time_t m_tmTime;

public:
	Time();														/**< default constructor */
	Time(Time_t tmTime);										/**< constructor with variable initialization */
	virtual ~Time();											/**< default destructor */

	void Increase() volatile;									/**< increases time by one second */

	void SetSecond(uint8_t nSecond) volatile;					/**< setter-method for second */
	void SetMinute(uint8_t nMinute) volatile;					/**< setter-method for minute */
	void SetHour(uint8_t nHour) volatile;						/**< setter-method for hour */

	uint8_t GetSecond() volatile;								/**< getter-method for second */
	uint8_t GetMinute() volatile;								/**< getter-method for minute */
	uint8_t GetHour() volatile;									/**< getter-method for hour */


	char* GetTimestring(bool bWithSecs) volatile;				/**< getter for formatted timestring */

	bool IsEqualTo(Time* oTime) volatile;						/**< check method for testing if times are equal */

	uint32_t GetDifferenceInSecs(Time *oTime) volatile;			/**< calculates the difference between two times in seconds */

};

#endif /* SRC_TIME_H_ */
