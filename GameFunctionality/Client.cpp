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
            ProcessResult(result);
            command = GetCommandFromUser();
            WriteStringToSocket(command);
            
            result.clear();
        }
    }
}

void Client::ProcessResult(const std::string& result)
{
    if (result.find_first_of("<") != -1) 
    {
        ParseResultString(result);
        mOutputManager->PrintScreen();
    } 
    else
    {
        FormattedPrint(result);
    }
}

void Client::ParseResultString(std::string inStr)
{
    std::string stateData = ConsumeTag(inStr);
    std::string statusData = ConsumeTag(inStr);
    std::string resultData = ConsumeTag(inStr);
    mState = ClientData::TranslateState(stateData);

    mOutputManager->StatusBar(statusData);
    mOutputManager->Output(resultData);

}

std::string Client::ConsumeTag(std::string& inStr)
{
    int tagStart = inStr.find("<");
    int tagEnd = inStr.find(">");
    tagStart++;
    std::string outputStr = inStr.substr(tagStart, tagEnd - 1);
    tagEnd++;
    inStr = inStr.substr(tagEnd);
    return outputStr;
}

std::string Client::GetCommandFromUser()
{
    std::string command;
    //std::cout << "Command: ";
    std::getline(std::cin, command);
    return command;
}
	
	