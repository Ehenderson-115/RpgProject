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
	std::shared_ptr<Parser> gameFileParser = std::make_shared<Parser>(Parser());
	PrintString("Welcome to the Untitled RPG Game. Press Enter to start!");
	std::getline(std::cin,response);
	mGameEntities = gameFileParser->ParseConfigFile("./Assets/config.txt");
	PrintString("File Parsed Successfully!");
}
