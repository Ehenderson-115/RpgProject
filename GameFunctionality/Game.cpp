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

bool Game::AddNewPlayer(const std::string& playerName)
{
	bool playerAdded = false;
	std::unique_lock<std::mutex> lock(mMutex);
	if (IsNewPlayer(playerName))
	{
		auto newPlayer = std::make_shared<Player>(playerName);
		mGameEntities.push_back(newPlayer);
		lock.unlock();
		auto startRoom = FindStartingRoom();
		auto world = std::static_pointer_cast<World>(mGameEntities.at(0));
		world->AddPlayerLocation(newPlayer, startRoom);
		auto outputManager = std::make_shared<OutputManager>();
		lock.lock();
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

std::string Game::GetPlayerStateString(const std::shared_ptr<ClientData>& playerData)
{
	std::string outputStr = "";
	outputStr += playerData->GetStateString();
	outputStr += playerData->GetStatusBar();
	outputStr += playerData->GetOutput();
	playerData->mOutputManager->Clear();
	return outputStr;
}

std::shared_ptr<ClientData> Game::GetPlayerData(const std::string& playerName)
{
	for (auto packet : mActivePlayerData)
	{
		if (packet->mPlayer->Name() == playerName)
		{
			return packet;
		}
	}
	return nullptr;
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

std::shared_ptr<ClientData> Game::FindAttackingPlayerData(const std::shared_ptr<Player>& inPlayer)
{
	for (auto packet : mActivePlayerData)
	{
		if (packet->mAdversary->Name() == inPlayer->Name())
		{
			return packet;
		}
	}
}

bool Game::CheckPlayerAttacked(std::shared_ptr<ClientData>& playerData)
{
	if ((playerData->State() == ClientData::GameState::Main || playerData->State() == ClientData::GameState::Menu) && playerData->mPlayer->InCombat())
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Game::InitPvp(std::shared_ptr<ClientData>& playerData)
{
	auto attacker = FindAttackingPlayerData(playerData->mPlayer);
	attacker->
}

std::string Game::ProcessUserCommand(const std::string playerName, const std::string userCommand)
{
	std::unique_lock<std::mutex> lock(mMutex);

	auto playerData = GetPlayerData(playerName);
	if (CheckPlayerAttacked(playerData))
	{
		InitPvp(playerData);
	}
	std::string output = "";
	
	auto command = mCommandParser->ParseCommandString(playerData, userCommand);
	lock.unlock();
	if (command == nullptr)
	{
		//If command is nullptr, then the command must have been invalid
		playerData->mOutputManager->AppendToOutput("Invalid Command: " + userCommand);
		output = GetPlayerStateString(playerData);
	}
	else
	{
		command->Execute();
		playerData->mOutputManager->UpdateStatusBar(playerData);
		if (playerData->State() == ClientData::GameState::Combat || playerData->State() == ClientData::GameState::CombatStart)
		{
			output = GetCombatResult(playerData);
		}
		else
		{
			output = GetPlayerStateString(playerData);
		}
	}
	return output;
}

std::string Game::GetCombatResult(std::shared_ptr<ClientData>& playerData)
{
	std::string output = "";
	if (playerData->mAdversary->Type() == Entity::ClassType::Player)
	{
		DoPvpCombat(playerData);
	}
	else
	{
		DoNpcCombat(playerData);
	}

	if (playerData->State() == ClientData::GameState::CombatEndClose)
	{
		playerData->mOutputManager->AppendToOutput("Press enter to exit the game...");
		output = GetPlayerStateString(playerData);
	}
	else if (playerData->State() == ClientData::GameState::CombatEndMain)
	{
		playerData->mOutputManager->AppendToOutput("Press enter to exit combat...");
		output = GetPlayerStateString(playerData);
		playerData->State(ClientData::GameState::Main);
	}
	else
	{
		output = GetPlayerStateString(playerData);
	}
	return output;
}

void Game::DoPvpCombat(std::shared_ptr<ClientData>& playerData)
{
	if (playerData->State() == ClientData::GameState::CombatStart)
	{
		playerData->mOutputManager->AppendToOutput("Waiting for other player...");
	}

}

void Game::DoNpcCombat(std::shared_ptr<ClientData>& playerData)
{
	if (IsCombatOver(playerData))
	{
		HandleCombatEnd(playerData);
	}
	else if(playerData->State() != ClientData::GameState::CombatStart)
	{
		ProcessAdversaryCommand(playerData);
	}
}

void Game::ProcessAdversaryCommand(std::shared_ptr<ClientData>& playerData)
{
	int enemyChoice = rand() % 2;
	std::string attack = "adv::Attack";
	std::string defend = "adv::Defend";
	std::lock_guard<std::mutex> lock(mMutex);
	if (enemyChoice == 0) 
	{
		auto command = mCommandParser->ParseCommandString(playerData, attack);
		command->Execute();
	}
	else
	{
		auto command = mCommandParser->ParseCommandString(playerData, defend);
		command->Execute();
	}
	playerData->mOutputManager->UpdateStatusBar(playerData);
}

bool Game::IsCombatOver(std::shared_ptr<ClientData>& playerData)
{
	if (playerData->mAdversary == nullptr)
	{
		return true;
	}
	else if (playerData->mPlayer->isDead() && !playerData->mAdversary->isDead())
	{
		return true;
	}
	else if (playerData->mAdversary->isDead() && !playerData->mPlayer->isDead())
	{
		return true;
	}
	else if (playerData->mPlayer->isDead() && playerData->mAdversary->isDead())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::HandleCombatEnd(std::shared_ptr<ClientData>& playerData)
{
	if (playerData->mPlayer->isDead() && !playerData->mAdversary->isDead())
	{
		playerData->mOutputManager->AppendToOutput("You have been killed by the " + playerData->mAdversary->Name() + ".\n");
		playerData->State(ClientData::GameState::CombatEndClose);
	}
	else if (playerData->mAdversary->isDead() && !playerData->mPlayer->isDead())
	{
		playerData->mOutputManager->AppendToOutput("The " + playerData->mAdversary->Name() + " has been killed.\n");
		playerData->State(ClientData::GameState::CombatEndMain);
		playerData->mRoom->RemoveContent(playerData->mAdversary->Name());
		playerData->mAdversary = nullptr;
	}
	else if (playerData->mPlayer->isDead() && playerData->mAdversary->isDead())
	{
		playerData->mOutputManager->AppendToOutput("You and the " + playerData->mAdversary->Name() + " deal lethal blows to one another.");
		playerData->mOutputManager->AppendToOutput("Just as the world begins to fade to black, you feel a burning spark of willpower. You refuse to give up.");
		playerData->mOutputManager->AppendToOutput(" 1 HP has been restored.\n");
		playerData->mPlayer->Heal(1);
		playerData->State(ClientData::GameState::CombatEndMain);
		playerData->mRoom->RemoveContent(playerData->mAdversary->Name());
		playerData->mAdversary = nullptr;
	}
}
