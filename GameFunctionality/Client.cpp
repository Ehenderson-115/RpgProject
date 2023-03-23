#include "Client.h"
#include <iostream>
#include <thread>
#include "HelperFunctions.h"


void Client::InitClient()
{
    std::string hostname = GetHostnameFromConfigFile("./ConfigFiles/NetworkConfig.txt");
    std::string port = GetPortFromConfigFile("./ConfigFiles/NetworkConfig.txt");
    ConnectToServer(hostname, port);
    MainLoop();
}

void Client::MainLoop()
{
    std::string result = "";
    std::string command = "";

    while (true)
    {
        if (result.empty())
        {
            result = ReadStringFromSocket();
            FormattedPrint(result);
            command = GetCommandFromUser();
            WriteStringToSocket(command);
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
	
	