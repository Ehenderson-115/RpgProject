#include "Server.h"
using asio::ip::tcp;

Server::Server(asio::io_context& io)
: ioContext(&io)
{
	acceptor = std::make_shared<tcp::acceptor>(io, tcp::endpoint(tcp::v4(), 13));
}



void Server::OpenConnection()
{

}

void Server::StartAccept()
{

}

void Server::HandleAccept()
{

}

