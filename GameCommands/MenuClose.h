#ifndef MENU_CLOSE_H
#define MENU_CLOSE_H
#include "GameCommand.h"

class MenuClose : public GameCommand
{
public:
	MenuClose(std::shared_ptr<ActiveGameData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif