#ifndef MAIN_OPEN_H
#define MAIN_OPEN_H
#include "GameCommand.h"

class MainOpen : public GameCommand
{
public:
	MainOpen(std::shared_ptr<ActiveGameData> inData, std::string inArgs);
	void Execute();

private:

};



#endif