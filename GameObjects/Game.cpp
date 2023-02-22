#include "Game.h"
#include "../GameCommands/CommandParser.h"
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
	case GameState::CombatStart:
		FormattedPrint(currPlayer->Character::GetStatus() + " ||| " + currAdversary->GetStatus());
		break;
	}
}

void Game::UpdateGameData()
{
	currRoom = activeData->mRoom;
	currPlayer = activeData->mPlayer;
	currAdversary = activeData->mAdversary;
	if (currState != activeData->mState)
	{
		UpdateState(activeData->mState);
	}
	
}

void Game::UpdateHud(const std::string& reprintStr)
{
	system("cls");
	PrintHud();
	if (!reprintStr.empty())
	{
		FormattedPrint(reprintStr);
	}
}

void Game::UpdateHud(const std::shared_ptr<ActiveGameData>& inData, const std::string& reprintStr)
{
	system("cls");
	PrintHud(inData);
	if (!reprintStr.empty())
	{
		FormattedPrint(reprintStr);
	}
}

void Game::PrintHud(const std::shared_ptr<ActiveGameData>& inData)
{
	switch (inData->mState)
	{
	case Game::GameState::Main:
		FormattedPrint("Current Location: " + inData->mRoom->Name() + "\n");
		break;
	case Game::GameState::Menu:
		FormattedPrint(inData->mPlayer->GetStatus() + "\n");
		break;
	case Game::GameState::Combat:
		FormattedPrint(inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus());
		break;
	case Game::GameState::CombatStart:
		FormattedPrint(inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus());
		break;
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

	commandParser = std::make_shared<CommandParser>();
	auto gameFileParser = std::make_shared<Parser>();

	mGameEntities = gameFileParser->InitGameDataFromFile("./Assets/config.txt");
	currPlayer = std::static_pointer_cast<Player>(mGameEntities.at(0));
	currRoom = std::static_pointer_cast<Room>(mGameEntities.at(currPlayer->RoomId()));
	currAdversary = nullptr;
	InitEntityPointers();


	srand(time(0));
	FormattedPrint("Data Loaded Successfully!");

	
	UpdateState(GameState::Main);
	activeData = std::make_shared<ActiveGameData>(currPlayer, currAdversary, currRoom, currState);
	GameLoop();
}

void Game::GameLoop()
{
	while (currState != GameState::Closing)
	{
		if (currPlayer->isDead())
		{
			MainClose();
		}
		getline(std::cin, commandInputStr);

		UpdateHud();
		
		commandInputStr = FormatCommand(commandInputStr);
		auto command = commandParser->ParseCommandString(activeData, commandInputStr);
		if (command != nullptr)
		{
			command->Execute();
			UpdateGameData();
		}
		else
		{
			PrintInvalidCommand(commandInputStr);
		}

		if (currState == GameState::Combat && !currAdversary->isDead())
		{
			ProcessAdversaryCommand();
		}

		commandInputStr.clear();
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

void Game::PrintInvalidCommand(const std::string& commmand)
{
	FormattedPrint("Invalid Command: " + commmand);
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