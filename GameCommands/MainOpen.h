#ifndef MAIN_OPEN_H
#define MAIN_OPEN_H
#include "GameCommand.h"

class MainOpen : public GameCommand
{
public:
	MainOpen(std::shared_ptr<ClientData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif