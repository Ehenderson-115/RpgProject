#include "Server.h"
#include "NetworkHandler.h"
#include "HelperFunctions.h"

void Server::InitServer()
{
	mGame = std::make_shared<Game>();
	mGame->InitGame();
	std::string portStr = GetPortFromConfigFile("./ConfigFiles/NetworkConfig.txt");
	FormattedPrint("Hosting server on port: " + portStr);
	ListenForNewClients(StringToValidPort(portStr));
}


void Server::ServerSession(int socketId)
{
	//Based on example code from the docs
	FormattedPrint("New Client Connected");
	asio::streambuf sbuf;
	asio::error_code error;
	std::string clientName = AddClientToGame(socketId);
	std::string clientCommand = "";
	std::string clientStatus = "";
	while (true)
	{
		//Waits for command to come in
		clientCommand = FormatCommand(ReadStringFromSocket(socketId));
		clientStatus = mGame->ExecuteCommand(clientName, clientCommand);

		//Updates the client with the status of their character
		WriteStringToSocket(clientStatus, socketId);
	}
}

std::string Server::AddClientToGame(int socketId)
{
	bool isValidName = false;
	WriteStringToSocket("Please enter the name of your character", socketId);
	std::string clientName = ReadStringFromSocket(socketId);
	isValidName = mGame->AddNewPlayer(clientName);
	while (!isValidName)
	{
		WriteStringToSocket("The name you provided is already being used by another player, please enter a new one", socketId);
		clientName = ReadStringFromSocket(socketId);
		isValidName = mGame->AddNewPlayer(clientName);
	}
	WriteStringToSocket("You have been successfully added to the game world!", socketId);
	return clientName;
}

