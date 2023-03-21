#include "Client.h"
#include <iostream>
#include "HelperFunctions.h"
#include "NetworkFunctions.h"


void Client::InitClient()
{
    InitServerConnection();
}


std::string Client::GetCommandFromUser()
{
    std::string command;
    std::cout << "Command: ";
    std::getline(std::cin, command);
    return command;
}
	
	