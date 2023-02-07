#include "Game.h"
#include "Player.h"
#include "Room.h"
#include "Entity.h"
#include "Character.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Item.h"
#include "HelperFunctions.h"
#include "Parser.h"


void Game::StartGame()
{
	std::string response;
	std::shared_ptr<Parser> gameFileParser = std::make_shared<Parser>();
	PrintString("Welcome to the Untitled RPG Game!");
	std::vector<std::shared_ptr<Entity>> tempVect;
	mGameEntities = gameFileParser->ParseConfigFile("./Assets/config.txt");
	currPlayer = std::static_pointer_cast<Player>(mGameEntities.at(0));
	currRoom = std::static_pointer_cast<Room>(mGameEntities.at(currPlayer->GetCurrRoomId()));
	PrintString("File Parsed Successfully!");
	GameLoop();
}

void Game::GameLoop()
{
	runGame = true;
	std::string command;
	while (runGame)
	{
		getline(std::cin, command);
		ParseCommand(command);

	}
}

void Game::ParseCommand(std::string& inCommandStr)
{
	std::vector<std::string> command;
	RemoveExtraSpaces(inCommandStr);
	BreakUpString(inCommandStr, command);
	ExecuteCommand(command);

}

void Game::ExecuteCommand(const std::vector<std::string>& inCommand)
{
	std::string type = inCommand.front();
	StrToLower(type);
	if (type == "move" || type == "goto")
	{

	}
	else if (type == "look" || type == "check")
	{
		PrintString(currRoom->GetDescript());
	}
	else if (type == "search" || type == "survey")
	{
		PrintString(currRoom->CheckRoomContents());
	}
	else if (type == "get" || type == "pickup")
	{
		PrintString("You picked up the " + inCommand.back());
	}
	else if (type == "engage" || type == "attack")
	{

	}
	else if (type == "exit" || type == "quit")
	{
		runGame = false;
	}
	else 
	{
		PrintString("Invalid Command: " + type);

	}
}
