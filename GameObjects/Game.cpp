#include "Game.h"
#include "Character.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Item.h"
#include "HelperFunctions.h"
#include "Parser.h"


void Game::StartGame()
{
	std::string response;
	auto gameFileParser = std::make_shared<Parser>();
	PrintString("Welcome to the Untitled RPG Game!");
	std::vector<std::shared_ptr<Entity>> tempVect;
	currState = GameState::Loading;

	mGameEntities = gameFileParser->InitGameDataFromFile("./Assets/config.txt");

	currPlayer = std::static_pointer_cast<Player>(mGameEntities.at(0));
	currRoom = std::static_pointer_cast<Room>(mGameEntities.at(currPlayer->GetCurrRoomId()));

	PrintString("Data Loaded Successfully!");
	currState = GameState::Main;
	GameLoop();
}

void Game::GameLoop()
{
	runGame = true;
	std::string command;
	while (runGame)
	{
		getline(std::cin, command);
		system("cls");
		ParseCommand(command);

	}
}

void Game::ParseCommand(std::string& inCommandStr)
{
	std::vector<std::string> command;
	RemoveExtraSpaces(inCommandStr);
	GrabNextWord(inCommandStr, command);
	ExecuteCommand(inCommandStr, command);

}

void Game::ExecuteCommand(std::string& inCommandStr, std::vector<std::string>& inCommandVect)
{
	std::string command = inCommandVect.front();
	std::string argument = "";
	StrToLower(command);
	switch (currState)
	{
	case GameState::Main:
		if (command == "move" || command == "goto")
		{
			GrabNextWord(inCommandStr, inCommandVect);
			argument = inCommandVect.back();
			StrToLower(argument);
			int nextRoomId = currRoom->GetRoom(argument);
			if (nextRoomId != NULL)
			{
				currPlayer->SetCurrRoomId(nextRoomId);
				currRoom = std::static_pointer_cast<Room>(mGameEntities.at(nextRoomId));
				PrintString("You enter the room");

			}
		}
		else if (command == "open")
		{
			GrabNextWord(inCommandStr, inCommandVect);
			argument = inCommandVect.back();
			StrToLower(argument);
			if (argument == "inventory" || argument == "inven")
			{
				currState = GameState::Menu;
			}
			else
			{
				PrintString("Invalid target " + argument);
			}
		}
		else if (command == "look" || command == "check")
		{
			PrintString(currRoom->Descript());
		}
		else if (command == "search" || command == "survey")
		{
			PrintString(currRoom->CheckRoomContents());
		}
		else if (command == "grab" || command == "pickup")
		{
			std::shared_ptr<Item> foundItem = currRoom->GetItem(inCommandStr);
			if (foundItem != nullptr)
			{
				currPlayer->AddItem(foundItem);
				PrintString("You picked up the " + inCommandStr);
			}
			else
			{
				PrintString("There is no item with the name " + inCommandStr);
			}
		}
		else if (command == "engage" || command == "attack")
		{

		}
		else if (command == "exit" || command == "quit")
		{
			runGame = false;
		}
		else
		{
			PrintString("Invalid Command: " + command);

		}
		break;
	case GameState::Menu:
		if (command == "list" || command == "ls")
		{
			PrintString(currPlayer->CheckInventory());
		}
		else if (command == "exit" || command == "close")
		{
			currState = GameState::Main;
		}
		else if (command == "examine" || command == "inspect")
		{
			PrintString(currPlayer->CheckItem(inCommandStr));
		}
		else if (command == "look")
		{
			GrabNextWord(inCommandStr, inCommandVect);
			argument = inCommandVect.back();
			StrToLower(argument);
			if (argument == "at")
			{
				PrintString(currPlayer->CheckItem(inCommandStr));
			}
			else 
			{
				PrintString("No look target specified");
			}
		}
		else if (command == "equip")
		{
			currPlayer->EquipWeapon(inCommandStr);
		}
		else
		{
			PrintString("Invalid Command: " + command + " try closing inventory first.");
		}
		break;
	case GameState::Combat:
		break;
		
	
	}

}
