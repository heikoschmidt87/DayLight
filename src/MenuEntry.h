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
	char *sMenuTitle_;
	void (*function_)();

	MenuEntry *next_;

public:
	MenuEntry(char *sTitle, void (*function)());
	virtual ~MenuEntry();

	char* GetMenuTitle();
	void SetMenuTitle(char *sTitle);

	void SetFunction(void (*function)());
	void Run();

	void SetNext(MenuEntry *next);
	MenuEntry* GetNext();
};

#endif /* SRC_MENUENTRY_H_ */
