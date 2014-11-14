/*
 * LcdMenu.h
 *
 *  Created on: 05.11.2014
 *      Author: heiko
 */

#ifndef SRC_LCDMENU_H_
#define SRC_LCDMENU_H_

////////////////////////////////////
// INCLUDES
////////////////////////////////////
#include "LCDisplay.h"
#include "MenuEntry.h"

////////////////////////////////////
// CLASS
////////////////////////////////////
typedef struct {
	volatile uint8_t *btnPin_;
	uint8_t btnNext_;
	uint8_t btnEnter_;

} ButtonConfig_t;

class LcdMenu {
private:
	MenuEntry *currentMenuEntry_;
	volatile LCDisplay *lcDisplay_;

	volatile uint8_t *nMenuSecondCounter_;

	ButtonConfig_t btnConfig_;

public:
	LcdMenu();
	LcdMenu(ButtonConfig_t btnConfig, volatile LCDisplay *lcDisplay, MenuEntry *currentMenuEntry_, volatile uint8_t *menuSecondCounter);
	virtual ~LcdMenu();

	void SetLCDisplay(LCDisplay *lcDisplay);
	volatile LCDisplay *GetLCDisplay();

	void SetMenuEntry(MenuEntry *menuEntry);
	MenuEntry *GetMenuEntry();

	void RunMenu();

	void SetButtonConfig(ButtonConfig_t btnConfig);
};

#endif /* SRC_LCDMENU_H_ */
