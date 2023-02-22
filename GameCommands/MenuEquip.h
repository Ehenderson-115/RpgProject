#ifndef MENU_EQUIP_H
#define MENU_EQUIP_H
#include "GameCommand.h"

class MenuEquip : public GameCommand
{
public:
	MenuEquip(std::shared_ptr<ActiveGameData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif