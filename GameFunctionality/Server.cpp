#include "Server.h"
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
	const int MAX_RETRY_COUNT = 3;
	//Based on example code from the docs
	FormattedPrint("New Client Connected");
	std::string clientName = AddClientToGame(socketId);
	std::string clientCommand = "";
	std::string clientStatus = "";
	bool writeSuccess = true;
	while (true)
	{
		//Waits for command to come in
		if(mGame->CheckPlayerAttacked(clientName))
		clientCommand = FormatCommand(ReadStringFromSocket(socketId));
		if (!clientCommand.empty())
		{
			clientStatus = mGame->ProcessUserCommand(clientName, clientCommand);
		}
		else
		{
			FormattedPrint("Failure to read message from client " + clientName + " closing connection...");
			break;
		}
		//Updates the client with the status of their character
		for(int i = 0; i <= MAX_RETRY_COUNT; i++)
		{
			writeSuccess = WriteStringToSocket(clientStatus, socketId);
			if (writeSuccess)
			{
				break;
			}
			else
			{
				FormattedPrint("Retrying...");
			}
		}
		if (!writeSuccess)
		{
			FormattedPrint("Failure to write message to client " + clientName + " closing connection...");
			break;
		}
	}
	SafelyCloseSocket(socketId);
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

