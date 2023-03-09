#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H
#include <string>
#include <memory>
#include "../GameObjects/ClientData.h"

class GameCommand
{
public:
	GameCommand(std::shared_ptr<ClientData> inData, std::string inArgs);
	virtual void Execute();

protected:
	std::string mArgs;
	std::shared_ptr<ClientData> mGameData;
};


#endif