#ifndef MAIN_CLOSE_H
#define MAIN_CLOSE_H
#include "GameCommand.h"

class MainClose : public GameCommand
{
public:
	MainClose(std::shared_ptr<ActiveGameData> inData, std::string inArgs);
	void Execute();

private:

};

#endif