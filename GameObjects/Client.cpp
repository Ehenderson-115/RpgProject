#include "Client.h"
#include <iostream>
#include "HelperFunctions.h"
#include "../ThirdPartyLibraries/asio-1.24.0/include/asio.hpp"

void Client::OpenConnection()
{
	std::string response;
	FormattedPrint("Hello World");
	std::getline(std::cin, response);
}
	
	