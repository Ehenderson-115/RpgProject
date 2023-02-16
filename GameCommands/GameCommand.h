#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H
#include <string>
#include "../GameObjects/ActiveGameData.h"

class GameCommand
{
public:
	GameCommand(ActiveGameData inData, std::string inArgs);
	void Execute();

private:
	std::string mArgs;
	ActiveGameData mGameData;
};


#endif