#ifndef MENU_INSPECT_H
#define MENU_INSPECT_H
#include "GameCommand.h"

class MenuInspect : public GameCommand
{
public:
	MenuInspect(std::shared_ptr<ActiveGameData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif