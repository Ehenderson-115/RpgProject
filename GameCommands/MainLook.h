#ifndef MAIN_LOOK_H
#define MAIN_LOOK_H
#include "GameCommand.h"

class MainLook : public GameCommand
{
public:
	MainLook(std::shared_ptr<ActiveGameData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif