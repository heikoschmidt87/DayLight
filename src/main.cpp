/*
 * main.cpp
 *
 *  Created on: 22.10.2014
 *      Author: heiko
 */

#include <avr/io.h>

#include "system.h"


/**
 *
 * @return
 */
int main() {

	bool bMenuStartAllowed = true;

	InitDayLightAlarm();

	lcDisplay->SetDisplayLight(true);

	sei();

	while(1) {

		/* check for refreshing DCF77 info */
		if(		((nFlags & FLAG_REFRESH_DCFTIME) > 0)
			&&	((nFlags & FLAG_DO_DCF_RECV) > 0)) {

			nFlags &= ~FLAG_REFRESH_DCFTIME;

			/* copy the DCF77 evaluated time to the current time and force display refresh */
			dtCurrentDateTime.SetHour(dtDcfData.GetHour());
			dtCurrentDateTime.SetMinute(dtDcfData.GetMinute());

			dtCurrentDateTime.SetDay(dtDcfData.GetDay());
			dtCurrentDateTime.SetDayOfWeek(dtDcfData.GetDayOfWeek());
			dtCurrentDateTime.SetMonth(dtDcfData.GetMonth());
			dtCurrentDateTime.SetYear(dtDcfData.GetYear());

			/* TODO: control second here or in ISR? */

			nFlags |= FLAG_REFRESH_DISPLAY;

		}

		/* refresh the display */
		if((nFlags & FLAG_REFRESH_DISPLAY) > 0) {

			lcDisplay->CurserPos(0, 1);
			lcDisplay->WriteString(dtCurrentDateTime.GetDatestring(true));
			lcDisplay->CurserPos(0, 2);
			lcDisplay->WriteString(dtCurrentDateTime.GetTimestring(true));

			if((nFlags & FLAG_UPDATE_DCF_DOT) > 0) {

				lcDisplay->CurserPos(15, 2);

				if((nFlags & FLAG_DCFSYMBOL_VISIBLE) > 0) {
					nFlags &= ~FLAG_DCFSYMBOL_VISIBLE;
					lcDisplay->WriteData(' ');
				} else {
					nFlags |= FLAG_DCFSYMBOL_VISIBLE;
					lcDisplay->WriteData('.');
				}

				nFlags &= ~FLAG_UPDATE_DCF_DOT;
			}

			nFlags &= ~FLAG_REFRESH_DISPLAY;
		}

		/* check for menu */
		if(ButtonPressed(&PIN_BTN1, BUTTON_MENU) && bMenuStartAllowed) {
			bMenuStartAllowed = false;

			lmLCDMenu->RunMenu();

			lcDisplay->ClearLCDisplay();
			lcDisplay->CursorHome();

			nFlags |= FLAG_REFRESH_DISPLAY;
		}

		/* check if button has been released */
		if(!bMenuStartAllowed) {
			if(!ButtonPressed(&PIN_BTN1, BUTTON_MENU))
				bMenuStartAllowed = true;
		}

	}


	return 0;
}

