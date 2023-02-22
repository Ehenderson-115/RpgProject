#ifndef MAIN_SEARCH_H
#define MAIN_SEARCH_H
#include "GameCommand.h"

class MainSearch : public GameCommand
{
public:
	MainSearch(std::shared_ptr<ActiveGameData> inData, std::string inArgs);
	virtual void Execute();

private:

};



#endif