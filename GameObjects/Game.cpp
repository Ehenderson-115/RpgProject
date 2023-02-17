#include "Game.h"
#include "../GameCommands/CommandProcessor.h"
#include "../GameCommands/GameCommand.h"
#include "ActiveGameData.h"
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

void Game::InitEntityPointers()
{
	for (auto entity : mGameEntities)
	{
		if (entity->classType() == Entity::ClassType::Room)
		{
			auto room = std::static_pointer_cast<Room>(entity);
			if (room->North() == nullptr && (room->RoomId("north") != -1))
			{
				auto roomToAdd = std::static_pointer_cast<Room>(mGameEntities.at(room->RoomId("north")));
				room->North(roomToAdd);
			}
			if (room->South() == nullptr && (room->RoomId("south") != -1))
			{
				auto roomToAdd = std::static_pointer_cast<Room>(mGameEntities.at(room->RoomId("south")));
				room->South(roomToAdd);
			}
			if (room->East() == nullptr && (room->RoomId("east") != -1))
			{
				auto roomToAdd = std::static_pointer_cast<Room>(mGameEntities.at(room->RoomId("east")));
				room->East(roomToAdd);
			}
			if (room->West() == nullptr && (room->RoomId("west") != -1))
			{
				auto roomToAdd = std::static_pointer_cast<Room>(mGameEntities.at(room->RoomId("west")));
				room->West(roomToAdd);
			}
		}
		else if (entity->classType() == Entity::ClassType::Player)
		{
			auto player = std::static_pointer_cast<Player>(entity);
			if (player->Location() == nullptr && player->RoomId() != -1)
			{
				auto roomToAdd = std::static_pointer_cast<Room>(mGameEntities.at(player->RoomId()));
				player->Location(roomToAdd);
			}
		}
	}
}

void Game::PrintHud()
{
	switch (currState)
	{
	case GameState::Main:
		FormattedPrint("Current Location: " + currRoom->Name() + "\n");
		break;
	case GameState::Menu:
		FormattedPrint(currPlayer->GetStatus() + "\n");
		break;

	case GameState::Combat:
		FormattedPrint(currPlayer->Character::GetStatus() + " ||| " + currAdversary->GetStatus());
		break;
	}
}

void Game::UpdateHud(std::string reprintStr="")
{
	system("cls");
	PrintHud();
	if (!reprintStr.empty())
	{
		FormattedPrint(reprintStr);
	}
}

void Game::UpdateState(GameState inState)
{
	currState = inState;
	UpdateHud();
}

void Game::StartGame()
{
	FormattedPrint("Welcome to the Untitled RPG Game!");
	currState = GameState::Loading;

	commandProcessor = std::make_shared<CommandProcessor>();
	auto gameFileParser = std::make_shared<Parser>();

	mGameEntities = gameFileParser->InitGameDataFromFile("./Assets/config.txt");
	currPlayer = std::static_pointer_cast<Player>(mGameEntities.at(0));
	currRoom = std::static_pointer_cast<Room>(mGameEntities.at(currPlayer->RoomId()));
	currAdversary = nullptr;

	activeData = std::make_shared<ActiveGameData>(currPlayer, currAdversary, currRoom, currState);

	srand(time(0));
	FormattedPrint("Data Loaded Successfully!");

	
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
		getline(std::cin, commandInputStr);

		UpdateHud();
		
		commandInputStr = FormatCommand(commandInputStr);
		commandProcessor ->ProcessCommandString(activeData, commandInputStr);
		
		//ProcessUserCommand();

		if (currState == GameState::Combat && !currAdversary->isDead() && !firstTurn)
		{
			ProcessAdversaryCommand();
		}

		commandInputStr.clear();
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
		ExecuteCombatCommand(command);
		break;
	}

}

void Game::ProcessAdversaryCommand()
{
	int enemyChoice = rand() % 2;
	if (enemyChoice == 0) 
	{
		CombatAttackAdversary();
	}
	else
	{
		CombatDefendAdversary();
	}

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
	commandInputStr = GrabNextArg(commandInputStr);
	argument = commands.back();


	int nextRoomId = currRoom->RoomId(argument);
	if (nextRoomId != -1 && nextRoomId != NULL)
	{
		currPlayer->RoomId(nextRoomId);
		currRoom = std::static_pointer_cast<Room>(mGameEntities.at(nextRoomId));
		UpdateHud();
		FormattedPrint("You enter the room.");
	}
	else if (nextRoomId == NULL) 
	{
		FormattedPrint("The direction \"" + argument + "\" is invalid.");
	}
	else
	{
		FormattedPrint("There is nothing in that direction.");
	}
}

void Game::MainSearch()
{
	FormattedPrint(currRoom->CheckRoomContents());
}

void Game::MainStartCombat()
{
	currAdversary = currRoom->GetCharacter(commandInputStr);
	if (currAdversary == nullptr)
	{
		FormattedPrint("The is no \"" + commandInputStr + "\" to fight.");
	}
	else
	{
		UpdateState(GameState::Combat);
		firstTurn = true;
	}
}

void Game::MainOpen()
{
	commandInputStr = GrabNextArg(commandInputStr);
	std::string argument = commands.back();
	if (argument == "inventory" || argument == "i")
	{
		UpdateState(GameState::Menu);
	}
	else
	{
		FormattedPrint("Invalid target " + argument);
	}
}

void Game::MainClose()
{
	runGame = false;
}

void Game::MainGrabItem()
{

	auto foundItem = currRoom->GetItem(commandInputStr);
	if (foundItem != nullptr)
	{
		currPlayer->AddItem(foundItem);
		FormattedPrint("You picked up the " + foundItem->Name());
	}
	else
	{
		FormattedPrint("There is no item with the name " + commandInputStr);
	}

}

void Game::InvalidCommand(const std::string& commmand)
{
	FormattedPrint("Invalid Command: " + commmand);
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
	FormattedPrint(currPlayer->CheckInventory());
}

void Game::MenuClose()
{
	UpdateState(GameState::Main);
}

void Game::MenuInspectItem()
{
	FormattedPrint(currPlayer->CheckItem(commandInputStr));
}

void Game::MenuLook()
{
	commandInputStr = GrabNextArg(commandInputStr);
	std::string argument = commands.back();
	if (argument == "at")
	{
		FormattedPrint(currPlayer->CheckItem(commandInputStr));
	}
	else
	{
		FormattedPrint("No look target specified");
	}
}

void Game::MenuEquip()
{
	std::string output = currPlayer->EquipWeapon(commandInputStr);
	UpdateHud();
	FormattedPrint(output);

}

//Combat Commands
void Game::ExecuteCombatCommand(const std::string& command)
{
	if (currAdversary->isDead() || currPlayer->isDead()) 
	{
		EndCombat();
		return;
	}
	if (command == "attack" || command == "a")
	{
		CombatAttackPlayer();
	}
	else if (command == "defend" || command == "d")
	{
		CombatDefendPlayer();
	}
	else if (command == "flee" || command == "f")
	{
		CombatFleePlayer();
	}
}

void Game::CombatAttackAdversary()
{
	int damageMod = (rand() % 5);
	int totalDamage;
	std::string turnDescript = "";
	std::string adversaryName = currAdversary->Name();
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
	UpdateHud(prevTurnResult);
	FormattedPrint(turnDescript);
	if (currPlayer->isDead())
	{
		FormattedPrint("You have been killed by the " + adversaryName + ".");
		FormattedPrint("Game Over. Press enter to exit...");
	};
}

void Game::CombatAttackPlayer()
{
	int damageMod = (rand() % 5);
	int totalDamage;
	std::string turnDescript = "";
	std::string adversaryName = currAdversary->Name();
	std::string wepName = currPlayer->GetWepName();
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
	FormattedPrint(turnDescript);
	if (firstTurn)
	{
		firstTurn = false;
	}
	if (currAdversary->isDead())
	{
		FormattedPrint("The " + adversaryName + " has been killed.");
		FormattedPrint("Press enter to exit combat...");
	}
}

void Game::CombatDefendAdversary()
{
	std::string turnResult = "The " + currAdversary->Name() + " prepares for you to attack.";
	currAdversary->Defend();
	FormattedPrint(turnResult);
}

void Game::CombatDefendPlayer()
{
	std::string turnResult = "You prepare for an oncoming attack.";
	currPlayer->Defend();
	FormattedPrint(turnResult);
}

//Unused for now
void Game::CombatFleePlayer()
{
	FormattedPrint("You cannot run from this fight!");
}

void Game::EndCombat()
{
	std::cin;
	currRoom->RemoveContent(currAdversary->Name());
	currAdversary = nullptr;
	UpdateState(GameState::Main);
}