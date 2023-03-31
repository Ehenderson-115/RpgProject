#include "GameCommand.h"
#include "HelperFunctions.h"

GameCommand::GameCommand(std::shared_ptr<ClientData> inData, std::string inArgs) 
	: mPlayerData{inData}
	, mArgs {inArgs}
{}
void GameCommand::Execute()
{
	FormattedPrint("Default command executed");
};

