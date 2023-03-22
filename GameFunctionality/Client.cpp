#include "Client.h"
#include <iostream>
#include <thread>
#include "HelperFunctions.h"
#include "NetworkFunctions.h"


void Client::Start()
{
    std::string result = "";
    std::string command = ""; 
    auto networkThread = std::make_shared<std::thread>(ClientSession, result, command);
    networkThread->detach();
    while (true)
    {
        if (!result.empty() && command.empty())
        {
            mOutputManager->Output(result);
            mOutputManager->PrintScreen();
            
        }
        if (!result.empty() && command.empty())
        {
            command = GetCommandFromUser();
            result.clear();
        }


    }

}


std::string Client::GetCommandFromUser()
{
    std::string command;
    //std::cout << "Command: ";
    std::getline(std::cin, command);
    return command;
}
	
	