#include "GameCommand.h"
#include "HelperFunctions.h"

GameCommand::GameCommand(std::shared_ptr<ClientData> inData, std::string inArgs) 
	: mGameData{inData}
	, mArgs {inArgs}
{}
void GameCommand::Execute()
{
	FormattedPrint("Default command executed");
};

