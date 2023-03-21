#include "Server.h"
#include "NetworkFunctions.h"
#include "HelperFunctions.h"
#include <thread>

void Server::InitServer()
{
	mGame = std::make_shared<Game>();
	mGame->InitGame();
	std::string portStr = GetPortFromConfigFile("./ConfigFiles/NetworkConfig.txt");
	FormattedPrint("Hosting server on port: " + portStr);
	AcceptClientConnections(StringToValidPort(portStr), mGame);
}



