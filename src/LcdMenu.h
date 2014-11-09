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
	uint8_t *btnPort_;
	uint8_t *btnDdr_;
	uint8_t btnNext_;
	uint8_t btnEnter_;

} ButtonConfig_t;

class LcdMenu {
private:
	MenuEntry *currentMenuEntry_;
	LCDisplay *lcDisplay_;

	ButtonConfig_t btnConfig_;

public:
	LcdMenu(ButtonConfig_t btnConfig, LCDisplay *lcDisplay, MenuEntry *currentMenuEntry_);
	virtual ~LcdMenu();

	void SetLCDisplay(LCDisplay *lcDisplay);
	LCDisplay *GetLCDisplay();

	void SetMenuEntry(MenuEntry *menuEntry);
	MenuEntry *GetMenuEntry();

	void RunMenu();

	void SetButtonConfig(ButtonConfig_t btnConfig);
};

#endif /* SRC_LCDMENU_H_ */
