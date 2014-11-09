/*
 * MenuEntry.h
 *
 *  Created on: 05.11.2014
 *      Author: heiko
 */

#ifndef SRC_MENUENTRY_H_
#define SRC_MENUENTRY_H_

////////////////////////////////////
// INCLUDES
////////////////////////////////////


////////////////////////////////////
// CLASS
////////////////////////////////////
class MenuEntry {
private:
	const char *sMenuTitle_;
	void (*function_)();

	MenuEntry *next_;

public:
	MenuEntry();
	MenuEntry(const char *sTitle, void (*function)(), MenuEntry *next);
	virtual ~MenuEntry();

	const char* GetMenuTitle() volatile;
	void SetMenuTitle(const char *sTitle) volatile;

	void SetFunction(void (*function)()) volatile;
	void Run() volatile;

	void SetNext(MenuEntry *next) volatile;
	MenuEntry* GetNext() volatile;
};

#endif /* SRC_MENUENTRY_H_ */
