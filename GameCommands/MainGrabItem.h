#ifndef MAIN_GRAB_ITEM_H
#define MAIN_GRAB_ITEM_H
#include "GameCommand.h"

class MainGrabItem : public GameCommand
{
public:
	MainGrabItem(std::shared_ptr<ActiveGameData> inData, std::string inArgs);
	void Execute();

private:

};



#endif