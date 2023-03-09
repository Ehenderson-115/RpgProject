#include "Client.h"
#include <iostream>

using asio::ip::tcp;

Client::Client(asio::io_context& io)
    :mIo(io)
    ,mSocket(mIo)
    ,mResolver(mIo)
{}

void Client::ConnectToServer()
{
    //Based on example code from the doc
    std::string host = "localhost";
    std::string port = "13";
    asio::connect(mSocket, mResolver.resolve(host.c_str(), port.c_str()));
    mIo.run();
    while (true)
    {
        std::cout << "Enter Message: ";
        char request[1024];
        std::cin.getline(request, 1024);
        size_t request_length = std::strlen(request);
        asio::write(mSocket, asio::buffer(request, request_length));

        char reply[1024];
        size_t reply_length = asio::read(mSocket, asio::buffer(reply, request_length));
        
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
}

void Client::GetUserCommand()
{

}
	
	