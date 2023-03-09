#ifndef MENU_LIST_ITEMS_H
#define MENU_LIST_ITEMS_H
#include "GameCommand.h"

class MenuListItems : public GameCommand
{
public:
	MenuListItems(std::shared_ptr<ClientData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif