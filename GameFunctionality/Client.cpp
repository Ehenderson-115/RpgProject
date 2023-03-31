#include "Client.h"
#include <iostream>
#include <thread>
#include "HelperFunctions.h"


void Client::InitClient()
{
    mOutputManager = std::make_shared<OutputManager>();
    mState = ClientData::GameState::Main;
    std::string hostname = GetHostnameFromConfigFile("./ConfigFiles/NetworkConfig.txt");
    std::string port = GetPortFromConfigFile("./ConfigFiles/NetworkConfig.txt");
    ConnectToServer(hostname, port);
    ClientSideSession();
}

void Client::ClientSideSession()
{
    std::string result = "";
    std::string command = "";

    while (true)
    {
        result = ReadStringFromSocket();
        ProcessResult(result);
        if (mState == ClientData::GameState::Closing) 
        {
            break;
        }
        else if (mState == ClientData::GameState::CombatEndClose) 
        {
            getline(std::cin, result);
            break;
        }
        else if (mState == ClientData::GameState::CombatEndMain) 
        {
            getline(std::cin, result);
            result.clear();
            WriteStringToSocket("look");
            continue;
        }
        command = GetCommandFromUser();
        WriteStringToSocket(command);
        result.clear();

    }
    SafelyCloseSocket();
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
    std::getline(std::cin, command);
    return command;
}
	
	