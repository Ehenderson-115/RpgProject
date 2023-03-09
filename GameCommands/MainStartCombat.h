#ifndef MAIN_START_COMBAT_H
#define MAIN_START_COMBAT_H
#include "GameCommand.h"

class MainStartCombat : public  GameCommand
{
public:
	MainStartCombat(std::shared_ptr<ClientData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif