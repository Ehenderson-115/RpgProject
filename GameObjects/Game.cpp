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
#include "Server.h"
#include <thread>
#include <time.h>
#include <random>

using asio::ip::tcp;

std::string Game::FormatCommand(std::string inStr)
{
	inStr = StrToLower(inStr);
	inStr = RemoveExtraSpaces(inStr);
	return inStr;
}

std::shared_ptr<Player> Game::CreatePlayer(const tcp::socket& socket)
{
	
	std::string playerName;
	FormattedPrint("Please enter the name of your character");
	getline(std::cin, playerName);
	auto newPlayer = std::make_shared<Player>(playerName);
	mMutex.lock();
	mGameEntities.push_back(newPlayer);
	mMutex.unlock();
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


void Game::InitServer()
{
	srand(time(0));
	mPort = GetPortFromUser();	
	mAcceptor = tcp::acceptor(mIo, tcp::endpoint(tcp::v4(), mPort));
	auto gameFileParser = std::make_shared<Parser>();
	mGameEntities = gameFileParser->InitGameDataFromFile("./Assets/config.txt");
	mStartingRoom = FindStartingRoom();
	mIo.run();
	AcceptNewClientConnections();
}


void Game::AcceptNewClientConnections()
{
	auto gamePtr = std::make_shared<Game>(*this);
	while (true)
	{
		std::make_shared<std::thread>(Session, mAcceptor.accept(), gamePtr)->detach();
	}
}

void Game::Session(tcp::socket socket, std::shared_ptr<Game> gamePtr)
{ 
	std::cout << "Thread Opened" << std::endl;
	asio::streambuf sbuf;
	asio::error_code error;
	std::string playerName = "";
	auto player = gamePtr->CreatePlayer(socket);
	while (true)
	{
		auto mutbuf = sbuf.prepare(1024);
		int msgLen = socket.read_some(mutbuf, error);
		if (error)
		{
			std::cout << "Thread Closed" << std::endl;
			return;
		}
		sbuf.commit(msgLen);
		if (playerName.empty())
		{
			auto conBuf = sbuf.data();
			playerName = std::string(asio::buffers_begin(conBuf),
				asio::buffers_begin(conBuf) + conBuf.size());
			std::cout << "Client Connected with id: " + playerName << std::endl;
		}
		sbuf.consume(1024);
		if (sbuf.size() > 0)
		{
			std::cout << "Sending Message To Client: " + playerName << std::endl;
			std::string testStr = "This is a string!";
			auto newBuf = asio::buffer(testStr, testStr.length());
			asio::write(socket, newBuf);
		}
	}
}

std::string Game::GetStringFromClient(const asio::ip::tcp::socket& inSocket)
{
	
}

void Game::WriteStringToClient(const asio::ip::tcp::socket& inSocket, std::string inStr)
{
	asio::write(inSocket, asio::buffer(inStr )
}


void Game::GameLoop()
{
	while (mActiveData->State() != ClientData::GameState::Closing)
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
		if (mActiveData->State() == ClientData::GameState::Combat || mActiveData->State() == ClientData::GameState::CombatStart)
		{
			DoCombatLogic();
		}
		if (mActiveData->State() == ClientData::GameState::CombatEndClose)
		{
			mActiveData->mOutputManager->AddToOutput("Press enter to exit the game...");
			mActiveData->mOutputManager->PrintScreen();
			getline(std::cin, mCommandStr);
		}
		else if (mActiveData->State() == ClientData::GameState::CombatEndMain)
		{
			mActiveData->mOutputManager->AddToOutput("Press enter to exit combat...");
			mActiveData->mOutputManager->PrintScreen();
			getline(std::cin, mCommandStr);
			mActiveData->State(ClientData::GameState::Main);
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
	else if(mActiveData->State() != ClientData::GameState::CombatStart)
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
		mActiveData->State(ClientData::GameState::CombatEndClose);
	}
	else if (mActiveData->mAdversary->isDead() && !mActiveData->mPlayer->isDead())
	{
		mActiveData->mOutputManager->AddToOutput("The " + mActiveData->mAdversary->Name() + " has been killed.\n");
		mActiveData->State(ClientData::GameState::CombatEndMain);
		mActiveData->mRoom->RemoveContent(mActiveData->mAdversary->Name());
		mActiveData->mAdversary = nullptr;
	}
	else if (mActiveData->mPlayer->isDead() && mActiveData->mAdversary->isDead())
	{
		mActiveData->mOutputManager->AddToOutput("You and the " + mActiveData->mAdversary->Name() + " deal lethal blows to one another.");
		mActiveData->mOutputManager->AddToOutput("Just as the world begins to fade to black, you feel a burning determination in your chest that won't let you die.");
		mActiveData->mOutputManager->AddToOutput("1 HP has been restored.\n");
		mActiveData->mPlayer->Heal(1);
		mActiveData->State(ClientData::GameState::CombatEndMain);
		mActiveData->mRoom->RemoveContent(mActiveData->mAdversary->Name());
		mActiveData->mAdversary = nullptr;
	}
}
