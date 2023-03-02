#include "GameCommand.h"
#include "../GameObjects/HelperFunctions.h"

GameCommand::GameCommand(std::shared_ptr<ActiveGameData> inData, std::string inArgs) 
	: mGameData{inData}
	, mArgs {inArgs}
{}
void GameCommand::Execute()
{
	FormattedPrint("Default command executed");
};

