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
#include <time.h>
#include <random>

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

	case GameState::Combat:
		PrintString(currPlayer->Character::GetStatus() + " ||| " + currAdversary->GetStatus());
		break;
	}
}

void Game::UpdateHud()
{
	system("cls");
	PrintHud();
}

void Game::UpdateState(GameState inState)
{
	currState = inState;
	UpdateHud();
}

void Game::StartGame()
{
	PrintString("Welcome to the Untitled RPG Game!");
	currState = GameState::Loading;

	auto gameFileParser = std::make_shared<Parser>();
	mGameEntities = gameFileParser->InitGameDataFromFile("./Assets/config.txt");
	currPlayer = std::static_pointer_cast<Player>(mGameEntities.at(0));
	currRoom = std::static_pointer_cast<Room>(mGameEntities.at(currPlayer->RoomId()));
	currAdversary = nullptr;
	srand(time(0));
	PrintString("Data Loaded Successfully!");

	
	UpdateState(GameState::Main);
	GameLoop();
}

void Game::GameLoop()
{
	runGame = true;
	while (runGame)
	{
		if (currPlayer->isDead())
		{
			MainClose();
		}
		getline(std::cin, commandStr);
		UpdateHud();
		
		commandStr = FormatCommand(commandStr);
		commandStr = GrabNextArg(commandStr);
		
		ProcessUserCommand();
		if (currState == GameState::Combat)
		{
			ProcessAdversaryCommand();
		}
		commandStr.clear();
		commands.clear();
	}
}

void Game::ProcessUserCommand()
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
		ExecuteCombatCommand(command, true);
		break;
		
	
	}

}

void Game::ProcessAdversaryCommand()
{
}

//Main Commands
void Game::ExecuteMainCommand(const std::string& command)
{
	if (command == "move" || command == "goto")
	{
		MainMove();
	}
	else if (command == "open")
	{
		MainOpen();
	}
	else if (command == "look" || command == "check")
	{
		MainLook();
	}
	else if (command == "search" || command == "survey")
	{
		MainSearch();
	}
	else if (command == "grab" || command == "pickup")
	{
		MainGrabItem();
	}
	else if (command == "engage" || command == "attack")
	{
		MainStartCombat();
	}
	else if (command == "exit" || command == "quit")
	{
		MainClose();
	}
	else
	{
		InvalidCommand(command);
	}
}

void Game::MainMove()
{
	std::string argument;
	commandStr = GrabNextArg(commandStr);
	argument = commands.back();


	int nextRoomId = currRoom->RoomConnection(argument);
	if (nextRoomId != -1 && nextRoomId != NULL)
	{
		currPlayer->RoomId(nextRoomId);
		currRoom = std::static_pointer_cast<Room>(mGameEntities.at(nextRoomId));
		UpdateHud();
		PrintString("You enter the room.");
	}
	else if (nextRoomId == NULL) 
	{
		PrintString("The direction \"" + argument + "\" is invalid.");
	}
	else
	{
		PrintString("There is nothing in that direction.");
	}
}

void Game::MainLook()
{
	PrintString(currRoom->Descript());
}

void Game::MainSearch()
{
	PrintString(currRoom->CheckRoomContents());
}

void Game::MainStartCombat()
{
	currAdversary = currRoom->GetCharacter(commandStr);
	if (currAdversary == nullptr)
	{
		PrintString("The is no \"" + commandStr + "\" to fight.");
	}
	else
	{
		UpdateState(GameState::Combat);
	}
}

void Game::MainOpen()
{
	commandStr = GrabNextArg(commandStr);
	std::string argument = commands.back();
	if (argument == "inventory" || argument == "i")
	{
		UpdateState(GameState::Menu);
	}
	else
	{
		PrintString("Invalid target " + argument);
	}
}

void Game::MainClose()
{
	runGame = false;
}

void Game::MainGrabItem()
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

void Game::InvalidCommand(const std::string& commmand)
{
	PrintString("Invalid Command: " + commmand);
}

//Menu Commands
void Game::ExecuteMenuCommand(const std::string& command)
{
	if (command == "list" || command == "ls")
	{
		MenuListItems();
	}
	else if (command == "exit" || command == "close")
	{
		MenuClose();
	}
	else if (command == "examine" || command == "inspect")
	{
		MenuInspectItem();
	}
	else if (command == "look")
	{
		MenuLook();
	}
	else if (command == "equip")
	{
		MenuEquip();
	}
	else
	{
		InvalidCommand(command);
	}
}

void Game::MenuListItems()
{
	PrintString(currPlayer->CheckInventory());
}

void Game::MenuClose()
{
	UpdateState(GameState::Main);
}

void Game::MenuInspectItem()
{
	PrintString(currPlayer->CheckItem(commandStr));
}

void Game::MenuLook()
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

void Game::MenuEquip()
{
	std::string output = currPlayer->EquipWeapon(commandStr);
	UpdateHud();
	PrintString(output);

}

//Combat Commands
void Game::ExecuteCombatCommand(const std::string& command, bool isPlayerAction)
{
	if (currAdversary->isDead() || currPlayer->isDead()) 
	{
		EndCombat();
		return;
	}
	if (command == "attack" || command == "a")
	{
		CombatAttack(isPlayerAction);
	}
	else if (command == "defend" || command == "d")
	{
		CombatDefend(isPlayerAction);
	}
	else if (command == "flee" || command == "f")
	{
		CombatFlee(isPlayerAction);
	}
}

void Game::CombatAttack(bool isPlayerAction)
{
	int damageMod = (rand() % 5);
	int totalDamage;
	std::string turnDescript = "";
	std::string adversaryName = currAdversary->Name();
	std::string wepName = currPlayer->GetWepName();
	if (isPlayerAction)
	{
		totalDamage = currPlayer->Attack(damageMod);
		if (damageMod == 4)
		{
			totalDamage *= 2;
			turnDescript += ("Your " + wepName + " begins to shine brightly.");
			turnDescript += " You feel your strength increase as you let loose a devastating attack.";
			turnDescript += " Critical Hit!";
		}
		else
		{
			turnDescript += ("You ready your " + wepName + " and strike the " + adversaryName + ".");
		}
		turnDescript += (" You deal " + std::to_string(totalDamage) + " to the " + adversaryName + ".");
		
		currAdversary->Damage(totalDamage);
		UpdateHud();
		PrintString(turnDescript);
		if (currAdversary->isDead())
		{
			PrintString("The " + adversaryName + " has been killed.");
			PrintString("Press enter to exit combat...");
		}
	}
	else
	{
		totalDamage = currAdversary->Attack(damageMod);
		if (damageMod == 4)
		{
			totalDamage *= 2;
			turnDescript += ("The " + adversaryName + " begins to glow.");
			turnDescript += " They strike you with double the strength they had previously.";
		}
		else
		{
			turnDescript += ("The " + adversaryName + " attacks you.");
		}
		turnDescript += " You take " + std::to_string(totalDamage) + " points of damage.";
		currPlayer->Damage(totalDamage);
		UpdateHud();
		PrintString(turnDescript);
		if (currPlayer->isDead())
		{
			PrintString("You have been killed by the " + adversaryName + ".");
			PrintString("Game Over. Press enter to exit...");
		};
	}
}

void Game::CombatDefend(bool isPlayerAction)
{
	if (isPlayerAction)
	{
		currPlayer->Defend();
		PrintString("You prepare for an oncoming attack.");
	}
	else
	{
		currAdversary->Defend();
		PrintString("The " + currAdversary->Name() + " prepares for an attack.");
	}
}

//Unused for now
void Game::CombatFlee(bool isPlayerAction)
{
	PrintString("You cannot run from this fight!");
}

void Game::EndCombat()
{
	std::cin;
	currRoom->RemoveContent(currAdversary->Name());
	currAdversary = nullptr;
	UpdateState(GameState::Main);
}