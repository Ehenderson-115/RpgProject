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
#include <time.h>
#include <random>

std::string Game::FormatCommand(std::string inStr)
{
	inStr = StrToLower(inStr);
	inStr = RemoveExtraSpaces(inStr);
	return inStr;
}

void Game::UpdateGameData()
{
	mCurrRoom = mActiveData->mRoom;
	mCurrPlayer = mActiveData->mPlayer;
	mCurrAdversary = mActiveData->mAdversary;
	mWorld = mActiveData->mWorld;
	if (mCurrState != mActiveData->mState)
	{
		UpdateState(mActiveData->mState);
	}
	mOutputManager = mActiveData->mOutputManager;
	mOutputManager->UpdateStatusBar(mActiveData);
}


void Game::UpdateState(GameState inState)
{
	if (mCurrState == GameState::CombatStart && inState == GameState::Combat)
	{
		mCurrState = inState;
	}
	else 
	{
		mCurrState = inState;
	}
	
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

void Game::StartGame()
{
	FormattedPrint("Welcome to the Untitled RPG Game!");
	mCurrState = GameState::Loading;
	mCommandParser = std::make_shared<CommandParser>();
	auto gameFileParser = std::make_shared<Parser>();

	mGameEntities = gameFileParser->InitGameDataFromFile("./Assets/config.txt");

	mCurrRoom = FindStartingRoom();
	mCurrPlayer = CreatePlayer();
	mCurrAdversary = nullptr;
	mWorld = std::static_pointer_cast<World>(mGameEntities.at(0));
	mWorld->AddPlayerLocation(mCurrPlayer, mCurrRoom);
	srand(time(0));

	mOutputManager = std::make_shared<OutputManager>();
	mActiveData = std::make_shared<ActiveGameData>(mCurrPlayer, mCurrAdversary, mCurrRoom, mWorld, mOutputManager, mCurrState);
	mActiveData->mState = Game::GameState::Main;
	UpdateGameData();
	mOutputManager->PrintScreen();
	GameLoop();
}

void Game::GameLoop()
{
	while (mCurrState != GameState::Closing)
	{
		getline(std::cin, mCommandStr);
		
		mCommandStr = FormatCommand(mCommandStr);
		auto command = mCommandParser->ParseCommandString(mActiveData, mCommandStr);
		if (command != nullptr)
		{
			command->Execute();
			UpdateGameData();
		}
		else
		{
			HandleInvalidCommand(mCommandStr);
		}
		if (mCurrState == GameState::Combat || mCurrState == GameState::CombatStart)
		{
			DoCombatLogic();
			UpdateGameData();
		}
		mOutputManager->PrintScreen();
		mCommandStr.clear();
	}
}

void Game::DoCombatLogic()
{
	if (isCombatOver())
	{
		HandleCombatEnd();
	}
	else if(mCurrState != GameState::CombatStart)
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
}

void Game::HandleInvalidCommand(const std::string& commmand)
{
	mOutputManager->AddToOutput("Invalid Command: " + commmand);
}

bool Game::isCombatOver()
{
	if (mCurrPlayer->isDead() && !mCurrAdversary->isDead())
	{
		return true;
	}
	else if (mActiveData->mAdversary->isDead() && !mCurrPlayer->isDead())
	{
		return true;
	}
	else if (mCurrPlayer->isDead() && mActiveData->mAdversary->isDead())
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
	if (mCurrPlayer->isDead() && !mCurrAdversary->isDead())
	{
		mActiveData->mOutputManager->AddToOutput("You have been killed by the " + mCurrAdversary->Name() + ".\n");
		mActiveData->mOutputManager->AddToOutput("Game Over. Press enter to exit...");
		getline(std::cin, mCommandStr);
		mActiveData->mState = Game::GameState::Closing;
	}
	else if (mActiveData->mAdversary->isDead() && !mCurrPlayer->isDead())
	{
		mActiveData->mOutputManager->AddToOutput("The " + mCurrAdversary->Name() + " has been killed.\n");
		mActiveData->mOutputManager->AddToOutput("Press enter to exit combat...");
		getline(std::cin, mCommandStr);
		mActiveData->mState = GameState::Main;
		mActiveData->mRoom->RemoveContent(mCurrAdversary->Name());
		mActiveData->mAdversary = nullptr;
	}
	else if (mCurrPlayer->isDead() && mActiveData->mAdversary->isDead())
	{
		mActiveData->mOutputManager->AddToOutput("You and the " + mCurrAdversary->Name() + " deal lethal blows to one another.\n");
		mActiveData->mOutputManager->AddToOutput("Just as the world begins to fade to black, you feel a burning determination in your chest that won't let you die.\n");
		mActiveData->mOutputManager->AddToOutput("1 HP has been restored.\n");
		mActiveData->mOutputManager->AddToOutput("Press enter to exit combat...");
		mActiveData->mPlayer->Heal(1);
		getline(std::cin, mCommandStr);
		mActiveData->mState = GameState::Main;
		mActiveData->mRoom->RemoveContent(mCurrAdversary->Name());
		mActiveData->mAdversary = nullptr;
	}
}
