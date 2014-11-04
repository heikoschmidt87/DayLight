/*
 * DateTime.h
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#ifndef SRC_DATETIME_H_
#define SRC_DATETIME_H_

/*
 * INCLUDES
 */
#include <inttypes.h>

/**
 * This is a class for representing date and time and enabling to compare dates and times.
 */
typedef struct {
	uint32_t nHour : 5;
	uint32_t nMinute : 6;
	uint32_t nSecond : 6;
} Time_t;

typedef struct {
	uint32_t nDayOfWeek : 3;
	uint32_t nDay : 5;
	uint32_t nMonth : 4;
	uint32_t nYear : 12;
} Date_t;


class DateTime {
protected:
	Time_t tmTime_;
	Date_t dtDate_;

public:
	/* TODO: use init list instead to increase performance */
	DateTime();													/**< default constructor */
	DateTime(Time_t tmTime, Date_t dtDate);						/**< constructor with variable initialization */
	virtual ~DateTime();										/**< default destructor */

	void Increase() volatile;									/**< increases time by one second and eventually date */

	void SetSecond(uint8_t nSecond) volatile;					/**< setter-method for second */
	void SetMinute(uint8_t nMinute) volatile;					/**< setter-method for minute */
	void SetHour(uint8_t nHour) volatile;						/**< setter-method for hour */

	void SetDayOfWeek(uint8_t nDayOfWeek) volatile;				/**< setter-method for day of week */
	void SetDay(uint8_t nDay) volatile;							/**< setter-method for day */
	void SetMonth(uint8_t nMonth) volatile;						/**< setter-method for month */
	void SetYear(uint16_t nYear) volatile;						/**< setter-method for year */

	uint8_t GetSecond() volatile;								/**< getter-method for second */
	uint8_t GetMinute() volatile;								/**< getter-method for minute */
	uint8_t GetHour() volatile;									/**< getter-method for hour */

	uint8_t GetDayOfWeek() volatile;							/**< getter-method for day of week */
	uint8_t GetDay() volatile;									/**< getter-method for day */
	uint8_t GetMonth() volatile;								/**< getter-method for month */
	uint16_t GetYear() volatile;								/**< getter-method for year */


	char* GetTimestring(bool bWithSecs) volatile;				/**< getter for formatted timestring */
	char* GetDatestring(bool bWithYear) volatile;				/**< getter for formatted date */


	bool IsTimeEqualTo(DateTime* oTime) volatile;						/**< check method for testing if times are equal */
	bool IsDateEqualTo(DateTime* oDate, bool bWithDayOfWeek) volatile;	/**< check method for testing if dates are equal */

	uint32_t GetTimeDifferenceInSecs(DateTime *oTime) volatile;			/**< calculates the difference between two times in seconds */

};

#endif /* SRC_DATETIME_H_ */
