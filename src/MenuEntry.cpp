/*
 * MenuEntry.cpp
 *
 *  Created on: 05.11.2014
 *      Author: heiko
 */

#include "MenuEntry.h"

MenuEntry::MenuEntry(char *sTitle, void (*function)()) {

	this->sMenuTitle_ = sTitle;
	this->function_ = function;
	this->next_ = 0;
}

MenuEntry::~MenuEntry() {
	// TODO Auto-generated destructor stub
}

char* MenuEntry::GetMenuTitle() {
	return this->sMenuTitle_;
}

void MenuEntry::SetMenuTitle(char *sTitle) {
	this->sMenuTitle_ = sTitle;
}

void MenuEntry::SetFunction(void (*function)()) {
	this->function_ = function;
}

void MenuEntry::Run() {
	this->function_();
}

void MenuEntry::SetNext(MenuEntry *next) {
	this->next_ = next;
}

MenuEntry* MenuEntry::GetNext() {
	return this->next_;
}
