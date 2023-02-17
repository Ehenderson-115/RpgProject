#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H
#include <string>
#include <memory>
#include "../GameObjects/ActiveGameData.h"

class GameCommand
{
public:
	GameCommand(std::shared_ptr<ActiveGameData> inData, std::string inArgs);
	void Execute();

protected:
	std::string mArgs;
	std::shared_ptr<ActiveGameData> mGameData;
};


#endif