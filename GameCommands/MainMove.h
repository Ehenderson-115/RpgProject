#ifndef MAIN_MOVE_H
#define MAIN_MOVE_H
#include "GameCommand.h"

class MainMove : public GameCommand
{
public:
	MainMove(std::shared_ptr<ClientData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif