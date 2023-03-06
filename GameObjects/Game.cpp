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
#include "World.h"
#include "OutputManager.h"
#include "../ThirdPartyLibraries/asio-1.24.0/include/asio.hpp"
#include "Server.h"
#include <time.h>
#include <random>

std::string Game::FormatCommand(std::string inStr)
{
	inStr = StrToLower(inStr);
	inStr = RemoveExtraSpaces(inStr);
	return inStr;
}

std::shared_ptr<Player> Game::CreatePlayer()
{
	std::string playerName;
	FormattedPrint("Please enter the name of your character");
	getline(std::cin, playerName);
	auto newPlayer = std::make_shared<Player>(playerName);
	mGameEntities.push_back(newPlayer);
	return newPlayer;
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

void Game::TestConnection()
{
	asio::io_context io_context;

	Server activeGameServer(io_context);


}

void Game::StartGame()
{
	FormattedPrint("Welcome to the Untitled RPG Game!");
	srand(time(0));

	mCommandParser = std::make_shared<CommandParser>();
	auto gameFileParser = std::make_shared<Parser>();

	mGameEntities = gameFileParser->InitGameDataFromFile("./Assets/config.txt");

	auto initRoom = FindStartingRoom();
	auto initPlayer = CreatePlayer();
	auto initWorld = std::static_pointer_cast<World>(mGameEntities.at(0));
	initWorld->AddPlayerLocation(initPlayer, initRoom);


	auto initOutputManager = std::make_shared<OutputManager>();
	mActiveData = std::make_shared<ActiveGameData>(initPlayer, nullptr, initRoom, initWorld, initOutputManager, Game::GameState::Main);
	mActiveData->State(Game::GameState::Main);
	mActiveData->mOutputManager->PrintScreen();
	GameLoop();
}

void Game::GameLoop()
{
	while (mActiveData->State() != GameState::Closing)
	{
		getline(std::cin, mCommandStr);
		
		mCommandStr = FormatCommand(mCommandStr);
		auto command = mCommandParser->ParseCommandString(mActiveData, mCommandStr);
		if (command != nullptr)
		{
			command->Execute();
			mActiveData->mOutputManager->UpdateStatusBar(mActiveData);
		}
		else
		{
			HandleInvalidCommand(mCommandStr);
		}
		if (mActiveData->State() == GameState::Combat || mActiveData->State() == GameState::CombatStart)
		{
			DoCombatLogic();
		}
		if (mActiveData->State() == GameState::CombatEndClose)
		{
			mActiveData->mOutputManager->AddToOutput("Press enter to exit the game...");
			mActiveData->mOutputManager->PrintScreen();
			getline(std::cin, mCommandStr);
		}
		else if (mActiveData->State() == GameState::CombatEndMain)
		{
			mActiveData->mOutputManager->AddToOutput("Press enter to exit combat...");
			mActiveData->mOutputManager->PrintScreen();
			getline(std::cin, mCommandStr);
			mActiveData->State(GameState::Main);
		}

		mActiveData->mOutputManager->PrintScreen();
		mCommandStr.clear();
	}
}

void Game::DoCombatLogic()
{
	if (isCombatOver())
	{
		HandleCombatEnd();
	}
	else if(mActiveData->State() != GameState::CombatStart)
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
		auto command = mCommandParser->ParseCommandString(mActiveData, attack);
		command->Execute();
	}
	else
	{
		auto command = mCommandParser->ParseCommandString(mActiveData, defend);
		command->Execute();
	}
	mActiveData->mOutputManager->UpdateStatusBar(mActiveData);
}

void Game::HandleInvalidCommand(const std::string& commmand)
{
	mActiveData->mOutputManager->AddToOutput("Invalid Command: " + commmand);
}

bool Game::isCombatOver()
{
	if (mActiveData->mAdversary == nullptr)
	{
		return true;
	}
	else if (mActiveData->mPlayer->isDead() && !mActiveData->mAdversary->isDead())
	{
		return true;
	}
	else if (mActiveData->mAdversary->isDead() && !mActiveData->mPlayer->isDead())
	{
		return true;
	}
	else if (mActiveData->mPlayer->isDead() && mActiveData->mAdversary->isDead())
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
	if (mActiveData->mPlayer->isDead() && !mActiveData->mAdversary->isDead())
	{
		mActiveData->mOutputManager->AddToOutput("You have been killed by the " + mActiveData->mAdversary->Name() + ".\n");
		mActiveData->State(Game::GameState::CombatEndClose);
	}
	else if (mActiveData->mAdversary->isDead() && !mActiveData->mPlayer->isDead())
	{
		mActiveData->mOutputManager->AddToOutput("The " + mActiveData->mAdversary->Name() + " has been killed.\n");
		mActiveData->State(GameState::CombatEndMain);
		mActiveData->mRoom->RemoveContent(mActiveData->mAdversary->Name());
		mActiveData->mAdversary = nullptr;
	}
	else if (mActiveData->mPlayer->isDead() && mActiveData->mAdversary->isDead())
	{
		mActiveData->mOutputManager->AddToOutput("You and the " + mActiveData->mAdversary->Name() + " deal lethal blows to one another.");
		mActiveData->mOutputManager->AddToOutput("Just as the world begins to fade to black, you feel a burning determination in your chest that won't let you die.");
		mActiveData->mOutputManager->AddToOutput("1 HP has been restored.\n");
		mActiveData->mPlayer->Heal(1);
		mActiveData->State(GameState::CombatEndMain);
		mActiveData->mRoom->RemoveContent(mActiveData->mAdversary->Name());
		mActiveData->mAdversary = nullptr;
	}
}
