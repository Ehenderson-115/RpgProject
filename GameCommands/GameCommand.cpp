#include "GameCommand.h"
#include "../GameObjects/HelperFunctions.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Room.h"
#include "../GameObjects/Character.h"

GameCommand::GameCommand(std::shared_ptr<ActiveGameData> inData, std::string inArgs) 
	: mGameData{inData}
	, mArgs {inArgs}
{};

void GameCommand::Execute()
{
	FormattedPrint("Command Executed!");
	FormattedPrint("Args Passed: " + mArgs);
	FormattedPrint("Player: " + mGameData->mPlayer->Name());
	FormattedPrint("Room: " + mGameData->mRoom->Name());
}
