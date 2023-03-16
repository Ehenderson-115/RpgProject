#include "Game.h"
#include "CommandParser.h"
#include "GameCommand.h"
#include "ClientData.h"
#include "Character.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"
#include "Room.h"
#include "Entity.h"
#include "Item.h"
#include "HelperFunctions.h"
#include "Parser.h"
#include "World.h"
#include "OutputManager.h"
#include <thread>
#include <time.h>
#include <random>
#include <iostream>


std::string Game::FormatCommand(std::string inStr)
{
	inStr = StrToLower(inStr);
	inStr = RemoveExtraSpaces(inStr);
	return inStr;
}

bool Game::AddNewPlayer(std::string playerName)
{
	bool playerAdded = false;
	if (IsNewPlayer(playerName))
	{
		auto newPlayer = std::make_shared<Player>(playerName);
		mGameEntities.push_back(newPlayer);
		auto startRoom = FindStartingRoom();
		auto world = std::static_pointer_cast<World>(mGameEntities.at(0));
		world->AddPlayerLocation(newPlayer, startRoom);
		auto outputManager = std::make_shared<OutputManager>();
		mActivePlayerData.push_back(std::make_shared<ClientData>(newPlayer, nullptr, startRoom, world, outputManager, ClientData::GameState::Main));
		playerAdded = true;
	}
	return playerAdded;
}

bool Game::IsNewPlayer(const std::string& playerName)
{
	for (auto entity : mGameEntities)
	{
		if (StrToLower(entity->Name()) == StrToLower(playerName))
		{
			return false;
		}
	}
	return true;
}

std::shared_ptr<Room> Game::FindStartingRoom()
{
	for (auto entity : mGameEntities)
	{
		if (StrToLower(entity->Name()) == "starting room")
		{
			return std::static_pointer_cast<Room>(entity);
		}
	}
	return nullptr;
}

void Game::InitGame()
{
	srand(time(0));
	auto gameFileParser = std::make_shared<Parser>();
	mGameEntities = gameFileParser->InitGameDataFromFile("./ConfigFiles/GameConfig.txt");
	mStartingRoom = FindStartingRoom();
}




void Game::GameLoop()
{
	while (mCurrPlayerData->State() != ClientData::GameState::Closing)
	{
		getline(std::cin, mCommandStr);
		
		mCommandStr = FormatCommand(mCommandStr);
		auto command = mCommandParser->ParseCommandString(mCurrPlayerData, mCommandStr);
		if (command != nullptr)
		{
			command->Execute();
			mCurrPlayerData->mOutputManager->UpdateStatusBar(mCurrPlayerData);
		}
		else
		{
			HandleInvalidCommand(mCommandStr);
		}
		if (mCurrPlayerData->State() == ClientData::GameState::Combat || mCurrPlayerData->State() == ClientData::GameState::CombatStart)
		{
			DoCombatLogic();
		}
		if (mCurrPlayerData->State() == ClientData::GameState::CombatEndClose)
		{
			mCurrPlayerData->mOutputManager->AddToOutput("Press enter to exit the game...");
			mCurrPlayerData->mOutputManager->PrintScreen();
			getline(std::cin, mCommandStr);
		}
		else if (mCurrPlayerData->State() == ClientData::GameState::CombatEndMain)
		{
			mCurrPlayerData->mOutputManager->AddToOutput("Press enter to exit combat...");
			mCurrPlayerData->mOutputManager->PrintScreen();
			getline(std::cin, mCommandStr);
			mCurrPlayerData->State(ClientData::GameState::Main);
		}

		mCurrPlayerData->mOutputManager->PrintScreen();
		mCommandStr.clear();
	}
}


void Game::DoCombatLogic()
{
	if (IsCombatOver())
	{
		HandleCombatEnd();
	}
	else if(mCurrPlayerData->State() != ClientData::GameState::CombatStart)
	{
		ProcessAdversaryCommand();
	}
}

void Game::ProcessAdversaryCommand()
{
	int enemyChoice = rand() % 2;
	std::string attack = "adv::Attack";
	std::string defend = "adv::Defend";
	if (enemyChoice == 0) 
	{
		auto command = mCommandParser->ParseCommandString(mCurrPlayerData, attack);
		command->Execute();
	}
	else
	{
		auto command = mCommandParser->ParseCommandString(mCurrPlayerData, defend);
		command->Execute();
	}
	mCurrPlayerData->mOutputManager->UpdateStatusBar(mCurrPlayerData);
}

void Game::HandleInvalidCommand(const std::string& commmand)
{
	mCurrPlayerData->mOutputManager->AddToOutput("Invalid Command: " + commmand);
}

bool Game::IsCombatOver()
{
	if (mCurrPlayerData->mAdversary == nullptr)
	{
		return true;
	}
	else if (mCurrPlayerData->mPlayer->isDead() && !mCurrPlayerData->mAdversary->isDead())
	{
		return true;
	}
	else if (mCurrPlayerData->mAdversary->isDead() && !mCurrPlayerData->mPlayer->isDead())
	{
		return true;
	}
	else if (mCurrPlayerData->mPlayer->isDead() && mCurrPlayerData->mAdversary->isDead())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::HandleCombatEnd()
{
	if (mCurrPlayerData->mPlayer->isDead() && !mCurrPlayerData->mAdversary->isDead())
	{
		mCurrPlayerData->mOutputManager->AddToOutput("You have been killed by the " + mCurrPlayerData->mAdversary->Name() + ".\n");
		mCurrPlayerData->State(ClientData::GameState::CombatEndClose);
	}
	else if (mCurrPlayerData->mAdversary->isDead() && !mCurrPlayerData->mPlayer->isDead())
	{
		mCurrPlayerData->mOutputManager->AddToOutput("The " + mCurrPlayerData->mAdversary->Name() + " has been killed.\n");
		mCurrPlayerData->State(ClientData::GameState::CombatEndMain);
		mCurrPlayerData->mRoom->RemoveContent(mCurrPlayerData->mAdversary->Name());
		mCurrPlayerData->mAdversary = nullptr;
	}
	else if (mCurrPlayerData->mPlayer->isDead() && mCurrPlayerData->mAdversary->isDead())
	{
		mCurrPlayerData->mOutputManager->AddToOutput("You and the " + mCurrPlayerData->mAdversary->Name() + " deal lethal blows to one another.");
		mCurrPlayerData->mOutputManager->AddToOutput("Just as the world begins to fade to black, you feel a burning determination in your chest that won't let you die.");
		mCurrPlayerData->mOutputManager->AddToOutput("1 HP has been restored.\n");
		mCurrPlayerData->mPlayer->Heal(1);
		mCurrPlayerData->State(ClientData::GameState::CombatEndMain);
		mCurrPlayerData->mRoom->RemoveContent(mCurrPlayerData->mAdversary->Name());
		mCurrPlayerData->mAdversary = nullptr;
	}
}
