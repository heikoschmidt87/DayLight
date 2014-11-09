/*
 * LcdMenu.cpp
 *
 *  Created on: 05.11.2014
 *      Author: heiko
 */

#include "LcdMenu.h"
#include "helpers.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

LcdMenu::LcdMenu() {
	this->lcDisplay_ = 0;
	this->currentMenuEntry_ = 0;
}

LcdMenu::LcdMenu(ButtonConfig_t btnConfig, volatile LCDisplay *lcDisplay, MenuEntry *currentMenueEntry, volatile uint8_t *menuSecondCounter) {

	this->lcDisplay_ = lcDisplay;
	this->btnConfig_ = btnConfig;
	this->currentMenuEntry_ = currentMenueEntry;
	this->nMenuSecondCounter_ = menuSecondCounter;
}

LcdMenu::~LcdMenu() {
	// TODO Auto-generated destructor stub
}

void LcdMenu::SetLCDisplay(LCDisplay *lcDisplay) {
	this->lcDisplay_ = lcDisplay;
}

volatile LCDisplay* LcdMenu::GetLCDisplay() {
	return this->lcDisplay_;
}

void LcdMenu::RunMenu() {

	bool bMenuActive = true;

	do {
		/* clear the display */
		this->lcDisplay_->ClearLCDisplay();
		this->lcDisplay_->CursorHome();

		/* print current menu title */
		this->lcDisplay_->WriteString(this->currentMenuEntry_->GetMenuTitle());

		/* check for button pressed */
		while(1) {
			/* check for "next" button to be pressed*/
			if(ButtonPressed(this->btnConfig_.btnPin_, this->btnConfig_.btnNext_)) {

				this->currentMenuEntry_ = this->currentMenuEntry_->GetNext();

				/* check if button is pressed longer than one second */
				if(ButtonPressed(this->btnConfig_.btnPin_, this->btnConfig_.btnNext_)) {
					bMenuActive = false;
				}

				/* wait till button is released */
				while(ButtonPressed(this->btnConfig_.btnPin_, this->btnConfig_.btnNext_)) {
				}

				break;
			}

			this->lcDisplay_->CurserPos(0, 2);
			char bla[16];

			/* check for "enter" button to be pressed */
			if(ButtonPressed(this->btnConfig_.btnPin_, this->btnConfig_.btnEnter_)) {

				this->lcDisplay_->WriteString("Druck");

				/* reset the button pressed timer */
				*this->nMenuSecondCounter_ = 0;


				_delay_ms(2000);

				int n = *this->nMenuSecondCounter_;
				sprintf(bla, "%d", n);
				this->lcDisplay_->WriteString(bla);

				while(true) {

				}

				/* wait for the button to be released */
				while(ButtonPressed(this->btnConfig_.btnPin_, this->btnConfig_.btnEnter_)) {
				}

				n = *this->nMenuSecondCounter_;
				sprintf(bla, "%d", n);
				this->lcDisplay_->WriteString(bla);

				while(1) {

				}

				/* check if the menu should be closed */
				if(*this->nMenuSecondCounter_ >= 10) {
					bMenuActive = false;
					break;

				} else {
					/* call the menu entry function */
				}
			}
		}

	} while (bMenuActive);
}

void LcdMenu::SetMenuEntry(MenuEntry *menuEntry) {
	this->currentMenuEntry_ = menuEntry;
}

MenuEntry* LcdMenu::GetMenuEntry() {
	return this->currentMenuEntry_;
}

void LcdMenu::SetButtonConfig(ButtonConfig_t btnConfig) {
	this->btnConfig_ = btnConfig;
}
