/*
 * MenuEntry.cpp
 *
 *  Created on: 05.11.2014
 *      Author: heiko
 */

#include "MenuEntry.h"

MenuEntry::MenuEntry() {
	this->sMenuTitle_ = 0;
	this->function_ = 0;
	this->next_ = 0;
}

MenuEntry::MenuEntry(const char *sTitle, void (*function)(), MenuEntry *next) {

	this->sMenuTitle_ = sTitle;
	this->function_ = function;
	this->next_ = next;
}

MenuEntry::~MenuEntry() {
	// TODO Auto-generated destructor stub
}

const char* MenuEntry::GetMenuTitle() volatile {
	return this->sMenuTitle_;
}

void MenuEntry::SetMenuTitle(const char *sTitle) volatile {
	this->sMenuTitle_ = sTitle;
}

void MenuEntry::SetFunction(void (*function)()) volatile {
	this->function_ = function;
}

void MenuEntry::Run() volatile {
	this->function_();
}

void MenuEntry::SetNext(MenuEntry *next) volatile {
	this->next_ = next;
}

MenuEntry* MenuEntry::GetNext() volatile {
	return this->next_;
}
