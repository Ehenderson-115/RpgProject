#include "Server.h"
#include <thread>
#include <string>
using asio::ip::tcp;

Server::Server(asio::io_context& io, const short inPort)
: mIo(io)
, mPort(inPort)
, mAcceptor(io, tcp::endpoint(tcp::v4(), mPort))

{}


void Server::CheckForNewClients()
{	
	mIo.run();
	while (true)
	{
		std::make_shared<std::thread>(Session, mAcceptor.accept())->detach();
	}
}

//Theoretically game commands
void Server::Session(tcp::socket socket)
{
	while (true)
	{
		
		asio::streambuf sbuf;
		sbuf._Lock();
		asio::streambuf::mutable_buffers_type mutbuf = sbuf.prepare(1024);
		asio::error_code error;
		int msgLen = socket.read_some(mutbuf, error);
		if (error)
			break; 
	
		sbuf.commit(msgLen);

		//Only echos back to the at the moment
		//Execute command would be here and the result string would be written back out the client through the socket.

		asio::write(socket, sbuf);
		sbuf._Unlock();
	}
}

void Server::HandleAccept()
{

}

