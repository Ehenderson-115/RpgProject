#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H
#include <memory>
#include <string>

class ActiveGameData;
class GameCommand;

class CommandParser
{
public:
	std::shared_ptr<GameCommand> GetCommand(ActiveGameData gameData, std::string command);

private:

};


#endif