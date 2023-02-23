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
	if (currState == GameState::CombatStart && inState == GameState::Combat)
	{
		currState = inState;
	}
	else 
	{
		currState = inState;
		UpdateHud();
	}
	
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
		if (currAdversary != nullptr && currAdversary->isDead())
		{
			EndCombat();
		}
		if (currState == GameState::Combat && !currAdversary->isDead())
		{
			ProcessAdversaryCommand();
		}
		if (currPlayer->isDead())
		{
			EndCombat();
			UpdateState(Game::GameState::Closing);
		}
		commandInputStr.clear();
	}
}

void Game::ProcessAdversaryCommand()
{
	int enemyChoice = rand() % 2;
	std::string attack = "adv::Attack";
	std::string defend = "adv::Defend";
	if (enemyChoice == 0) 
	{
		auto command = commandParser->ParseCommandString(activeData, attack);
		command->Execute();
		UpdateGameData();
	}
	else
	{
		auto command = commandParser->ParseCommandString(activeData, defend);
		command->Execute();
		UpdateGameData();
	}

}

void Game::PrintInvalidCommand(const std::string& commmand)
{
	FormattedPrint("Invalid Command: " + commmand);
}

void Game::EndCombat()
{
	getline(std::cin, commandInputStr);
	activeData->mRoom->RemoveContent(currAdversary->Name());
	activeData->mAdversary = nullptr;
	activeData->mState = GameState::Main;
	UpdateGameData();
}