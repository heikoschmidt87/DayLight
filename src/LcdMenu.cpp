/*
 * LcdMenu.cpp
 *
 *  Created on: 05.11.2014
 *      Author: heiko
 */

#include "LcdMenu.h"

LcdMenu::LcdMenu(ButtonConfig_t btnConfig, LCDisplay *lcDisplay) {

	this->lcDisplay_ = lcDisplay;
	this->btnConfig_ = btnConfig;
}

LcdMenu::~LcdMenu() {
	// TODO Auto-generated destructor stub
}

void LcdMenu::SetLCDisplay(LCDisplay *lcDisplay) {
	this->lcDisplay_ = lcDisplay;
}

LCDisplay* LcdMenu::GetLCDisplay() {
	return this->lcDisplay_;
}

void LcdMenu::RunMenu() {
}

void LcdMenu::SetMenuEntry(MenuEntry *menuEntry) {
	this->menuEntry_ = menuEntry;
}

MenuEntry* LcdMenu::GetMenuEntry() {
	return this->menuEntry_;
}

void LcdMenu::SetButtonConfig(ButtonConfig_t btnConfig) {
	this->btnConfig_ = btnConfig;
}
