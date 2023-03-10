#include "Client.h"
#include <iostream>
#include "HelperFunctions.h"

using asio::ip::tcp;

Client::Client()
    :mIo()
    , mSocket(mIo)
    , mPort(GetPortFromUser())
    , mResolver(mIo, mPort)
{}

void Client::InitServerConnection()
{
    //Based on example code from the doc
    std::string hostname = "localhost";
    asio::streambuf sbuf;
    asio::error_code error;
    asio::connect(mSocket, mResolver.resolve(hostname,std::to_string(mPort)));
    mIo.run();
    while (true)
    {
        auto command = GetCommandFromUser();
        asio::write(mSocket, asio::buffer(command, command.length()));

        auto mutbuf = sbuf.prepare(1024);
        int msgLen = mSocket.read_some(mutbuf, error);
        sbuf.commit(msgLen);
        auto conBuf = sbuf.data();
        auto reply = std::string(asio::buffers_begin(conBuf),
            asio::buffers_begin(conBuf) + conBuf.size());
        std::cout << "Response: " + reply << std::endl;
        sbuf.consume(1024);
        reply.clear();
        
    }
}

std::string Client::GetCommandFromUser()
{
    std::string command; 
    std::getline(std::cin, command);
    return command;
}
	
	