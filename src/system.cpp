/*
 * system.cpp
 *
 *  Created on: 04.10.2014
 *      Author: heiko
 */

#include "system.h"

////////////////////////////////////
// GLOBALS
////////////////////////////////////
volatile DateTime dtCurrentDateTime;
volatile DateTime tmAlarmTime;
volatile DcfData dtDcfData;

volatile uint8_t nClockOverflows;
volatile uint8_t nFlags;


volatile uint64_t nBitSequenceTime;
volatile uint64_t nBitTime;
volatile uint8_t nLowLevelTicks;
volatile uint8_t nCurrentBitNumber;

////////////////////////////////////
// FUNCTIONS
////////////////////////////////////
void * operator new (size_t size) {
	return malloc(size);
}

void operator delete(void * ptr) {
	free(ptr);
}

void InitFlags() {

	nFlags = 0;
}

void InitDayLightAlarm() {

	/*
	 * init buttons
	 */

	/* set outputs */
	DDR_BTN1 &= ~((1 << BUTTON_SNOOZE) | (1 << BUTTON_MENU) | (1 << BUTTON_ADJUST));
	DDR_BTN2 &= ~(1 << BUTTON_LIGHT);

	/* activate internal pullups */
	PORT_BTN1 |= (1 << BUTTON_SNOOZE) | (1 << BUTTON_MENU) | (1 << BUTTON_ADJUST);
	PORT_BTN2 |= (1 << BUTTON_LIGHT);


	/*
	 * init DayLight
	 */
	DDR_DAY_LIGHT |= (1 << DAY_LIGHT);
	PORT_DAY_LIGHT &= ~(1 << DAY_LIGHT);

	/*
	 * init speaker
	 */
	DDR_SPEAKER |= (1 << SPEAKER);
	PORT_SPEAKER &= (1 << SPEAKER);

	/* TODO: test speaker */

	/*
	 * init display light
	 */
	DDR_DISPLIGHT |= (1 << DISPLAY_LIGHT);
	PORT_DISPLIGHT &= ~(1 << DISPLAY_LIGHT);

	/* play test tone */
	/*
	 * PWM Timer for light and speaker
	 * PWM mode, no Prescaler, OC1/OC2 on
	 */
	TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1);
	TCCR1B = (1<<WGM12) | (1 << CS10);

	/* test sound and daylight output */
	OCR1A = 255;
	OCR1B = 100;		/* TODO: sound output test */

	_delay_ms(1000);

	OCR1A = 0;
	OCR1B = 0;

	/* switch off both pwm signals */
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1B1));

	/*
	 * init display
	 */
	lcd_init();
	lcd_clear();

	/*
	 * init DCF77
	 */
	/* set input for external Interrupt */
	DDRD &= ~(1 << PD2);

	/* timer for DCF77 bit decoding */
	TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << WGM21);		// Prescaler 256 and CTC mode
	TIMSK |= (1 << OCIE2);									// ISR on compare match
	TCNT2 = 0;
	OCR2 = 90;												// TODO: correction value!

	/* INT0 external interrupt for getting bit time -- arm rising edge initially */
	MCUCR |= (1 << ISC01) | (1 << ISC00);
	GICR |= (1 << INT0);

	/*
	 * init "normal" clock
	 */
	TCCR0 = (1 << CS02);
	TIMSK |= (1 << TOIE0);
}

ISR(TIMER0_OVF_vect) {

	if(++nClockOverflows >= 64) {
		nClockOverflows = 0;

		/* increase the time and adjust date if needed */
		dtCurrentDateTime.Increase();

		if(		(dtCurrentDateTime.GetHour() == 0)
			&&	(dtCurrentDateTime.GetMinute() == 0)
			&&	(dtCurrentDateTime.GetSecond() == 0)) {
		}

		nFlags |= FLAG_REFRESH_DISPLAY;
	}
}

ISR(INT0_vect) {

	/* disable external interrupt while handling */
	GICR &= ~(1 << INT0);

	if((nFlags & FLAG_DCF_FALLING_EDGE) > 0) {

		/* a new bit starts */
		nBitSequenceTime = nBitTime;	/* this is the total number of ticks between two bits */
		nBitTime = 0;					/* this holds the bit time */

		/* arm on the rising edge to determine the bit time */
		nFlags &= ~FLAG_DCF_FALLING_EDGE;
		MCUCR |= (1 << ISC01) | (1 << ISC00);

		/* toggle the symbol for DCF77 signal receiving */
		nFlags |= FLAG_UPDATE_DCF_DOT;

		/* determine if there is a minute change */
		if(nBitSequenceTime > 250) {

			/* check if all bits have been received -- only then update free running time */
			if(nCurrentBitNumber == 59) {
				/* make the DCF data to update the time */
				nFlags |= FLAG_REFRESH_DCFTIME;

				/* TODO: evaluate time here? */
				dtDcfData.EvaluateDateTime(true);

				/* reset the free running second timer */
				nClockOverflows = 0;
				TCNT0 = 0;
				dtCurrentDateTime.SetSecond(0);
			}

			/* reset the current bit number */
			nCurrentBitNumber = 0;
		}

	} else {

		/* save the low level bit time and therefore the bit value
		 * 200ms --> "1", 100ms --> "0" */
		nLowLevelTicks = nBitTime;

		/* add the bit to the DCF77 structure */
		if(nLowLevelTicks > 30) {
			dtDcfData.AddBit(nCurrentBitNumber, 1);
		} else {
			dtDcfData.AddBit(nCurrentBitNumber, 0);
		}

		/* increase the current bit number */
		nCurrentBitNumber++;

		/* react in falling edge at INT0 again */
		nFlags |= FLAG_DCF_FALLING_EDGE;

		MCUCR |= (1 << ISC01);
		MCUCR &= ~(1 << ISC00);
	}


	GICR |= (1 << INT0);
}

ISR(TIMER2_COMP_vect) {
	/* increase the bit time */
	nBitTime++;
}
