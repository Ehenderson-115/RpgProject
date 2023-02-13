#include "Game.h"
#include "Character.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"
#include "Room.h"
#include "Entity.h"
#include "Item.h"
#include "HelperFunctions.h"
#include "Parser.h"

std::string Game::FormatCommand(std::string inStr)
{
	inStr = StrToLower(inStr);
	inStr = RemoveExtraSpaces(inStr);
	return inStr;
}

std::string Game::GrabNextArg(std::string inStr)
{
	int firstSpace = inStr.find(" ");
	commands.push_back(inStr.substr(0, firstSpace));
	inStr = inStr.substr(firstSpace + 1);
	return inStr;

}

void Game::PrintHud()
{
	switch (currState)
	{
	case GameState::Main:
		PrintString("Current Location: " + currRoom->Name() + "\n");
		break;
	case GameState::Menu:
		PrintString(currPlayer->GetStatus() + "\n");
		break;
	}
}

void Game::UpdateHud()
{
	system("cls");
	PrintHud();
}

void Game::StartGame()
{
	PrintString("Welcome to the Untitled RPG Game!");
	currState = GameState::Loading;

	auto gameFileParser = std::make_shared<Parser>();
	mGameEntities = gameFileParser->InitGameDataFromFile("./Assets/config.txt");
	currPlayer = std::static_pointer_cast<Player>(mGameEntities.at(0));
	currRoom = std::static_pointer_cast<Room>(mGameEntities.at(currPlayer->RoomId()));
	PrintString("Data Loaded Successfully!");
	
	currState = GameState::Main;
	GameLoop();
}

void Game::GameLoop()
{
	runGame = true;
	while (runGame)
	{
		getline(std::cin, commandStr);
		system("cls");
		PrintHud();
		
		commandStr = FormatCommand(commandStr);
		commandStr = GrabNextArg(commandStr);
		
		ProcessUserCommands();
		
		commandStr.clear();
		commands.clear();
	}
}

void Game::ProcessUserCommands()
{
	std::string command = commands.front();
	std::string argument = "";
	switch (currState)
	{
	case GameState::Main:
		ExecuteMainCommand(command);
		break;
	case GameState::Menu:
		ExecuteMenuCommand(command);
		break;
	case GameState::Combat:
		break;
		
	
	}

}

//Main Commands
void Game::ExecuteMainCommand(const std::string& command)
{
	if (command == "move" || command == "goto")
	{
		Main_Move();
	}
	else if (command == "open")
	{
		Main_Open();
	}
	else if (command == "look" || command == "check")
	{
		Main_Look();
	}
	else if (command == "search" || command == "survey")
	{
		Main_Search();
	}
	else if (command == "grab" || command == "pickup")
	{
		Main_GrabItem();
	}
	else if (command == "engage" || command == "attack")
	{
		Main_StartCombat();
	}
	else if (command == "exit" || command == "quit")
	{
		Main_Close();
	}
	else
	{
		InvalidCommand(command);
	}
}

void Game::Main_Move()
{
	std::string argument;
	commandStr = GrabNextArg(commandStr);
	argument = commands.back();
	

	int nextRoomId = currRoom->RoomConnection(argument);
	if (nextRoomId != NULL)
	{
		currPlayer->RoomId(nextRoomId);
		currRoom = std::static_pointer_cast<Room>(mGameEntities.at(nextRoomId));
		PrintString("You enter the room");
	}
}

void Game::Main_Look()
{
	PrintString(currRoom->Descript());
}

void Game::Main_Search()
{
	if (currState == GameState::Main)
	{
		PrintString(currRoom->CheckRoomContents());
	}
}

void Game::Main_StartCombat()
{

}

void Game::InvalidCommand(const std::string& commmand)
{
	PrintString("Invalid Command: " + commmand);
}

void Game::Main_Open()
{
	commandStr = GrabNextArg(commandStr);
	std::string argument = commands.back();
	if (argument == "inventory" || argument == "i")
	{
		currState = GameState::Menu;
		UpdateHud();
	}
	else
	{
		PrintString("Invalid target " + argument);
	}
}

void Game::Main_Close()
{
	runGame = false;
}

void Game::Main_GrabItem()
{

	std::shared_ptr<Item> foundItem = currRoom->GetItem(commandStr);
	if (foundItem != nullptr)
	{
		currPlayer->AddItem(foundItem);
		PrintString("You picked up the " + foundItem->Name());
	}
	else
	{
		PrintString("There is no item with the name " + commandStr);
	}

}

//Menu Commands
void Game::ExecuteMenuCommand(const std::string& command)
{
	if (command == "list" || command == "ls")
	{
		Menu_ListItems();
	}
	else if (command == "exit" || command == "close")
	{
		Menu_Close();
	}
	else if (command == "examine" || command == "inspect")
	{
		Menu_InspectItem();
	}
	else if (command == "look")
	{
		Menu_Look();
	}
	else if (command == "equip")
	{
		Menu_Equip();
	}
	else
	{
		InvalidCommand(command);
	}
}

void Game::Menu_ListItems()
{
	PrintString(currPlayer->CheckInventory());
}

void Game::Menu_Close()
{
	currState = GameState::Main;
	UpdateHud();
}

void Game::Menu_InspectItem()
{
	PrintString(currPlayer->CheckItem(commandStr));
}

void Game::Menu_Look()
{
	commandStr = GrabNextArg(commandStr);
	std::string argument = commands.back();
	if (argument == "at")
	{
		PrintString(currPlayer->CheckItem(commandStr));
	}
	else
	{
		PrintString("No look target specified");
	}
}

void Game::Menu_Equip()
{
	std::string output = currPlayer->EquipWeapon(commandStr);
	UpdateHud();
	PrintString(output);

}