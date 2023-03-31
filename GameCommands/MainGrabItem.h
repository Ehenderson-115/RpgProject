#ifndef MAIN_GRAB_ITEM_H
#define MAIN_GRAB_ITEM_H
#include "GameCommand.h"

class MainGrabItem : public GameCommand
{
public:
	MainGrabItem(std::shared_ptr<ClientData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif