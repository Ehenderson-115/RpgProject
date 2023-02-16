#include "GameCommand.h"
#include "../GameObjects/HelperFunctions.h"

GameCommand::GameCommand(ActiveGameData inData, std::string inArgs) 
	: mGameData{inData}
	, mArgs {inArgs}
{};

void GameCommand::Execute()
{
	FormattedPrint("Command Executed!");
	FormattedPrint("Args Passed: " + mArgs);
}
