#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H
#include <memory>
#include <string>

struct ClientData;
class GameCommand;

class CommandParser
{
public:
	std::shared_ptr<GameCommand> ParseCommandString(std::shared_ptr<ClientData>& gameData, std::string& commandStr);
private:
	std::shared_ptr<GameCommand> GenerateMainCommand(std::shared_ptr<ClientData>& gameData, std::string& commandStr);
	std::shared_ptr<GameCommand> GenerateMenuCommand(std::shared_ptr<ClientData>& gameData, std::string& commandStr);
	std::shared_ptr<GameCommand> GenerateCombatCommand(std::shared_ptr<ClientData>& gameData, std::string& commandStr);

};


#endif