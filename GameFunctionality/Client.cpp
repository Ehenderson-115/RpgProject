#include "Client.h"
#include <iostream>
#include "HelperFunctions.h"


void Client::InitClient()
{
    //Based on example code from the doc
    std::string hostname = GetHostnameFromConfigFile("./Assets/NetworkConfig.txt");

    FormattedPrint("Attempting to connect to a server...");
    asio::connect(mSocket, mResolver.resolve(hostname,std::to_string(mPort)));
    FormattedPrint("Connection Successful");
    mIo.run();
    LogicLoop();
}

void Client::LogicLoop()
{
    asio::streambuf sbuf;
    asio::error_code error;

    while (true)
    {
        auto command = GetCommandFromUser();
        asio::write(mSocket, asio::buffer(command, command.length()));

        auto mutbuf = sbuf.prepare(1024);
        int msgLen = mSocket.read_some(mutbuf, error);
        if (error)
        {
            FormattedPrint("Connection closed press enter to exit...");
            std::getline(std::cin, command);
            break;
        }

        sbuf.commit(msgLen);
        auto conBuf = sbuf.data();
        auto reply = std::string(asio::buffers_begin(conBuf),
            asio::buffers_begin(conBuf) + conBuf.size());
        FormattedPrint(reply);
        sbuf.consume(1024);
        reply.clear();
        
    }

}

std::string Client::GetCommandFromUser()
{
    std::string command;
    std::cout << "Command: ";
    std::getline(std::cin, command);
    return command;
}
	
	