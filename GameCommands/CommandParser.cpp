#include "CommandParser.h"
#include "GameCommand.h"
#include "../GameObjects/ActiveGameData.h"
#include "../GameObjects/HelperFunctions.h"

std::shared_ptr<GameCommand> CommandParser::GetCommand(ActiveGameData gameData, std::string command)
{
	return std::make_shared<GameCommand>(gameData, command);
}
