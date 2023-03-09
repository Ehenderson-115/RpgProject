#include "Server.h"
#include <thread>
#include <string>
#include <iostream>
#include <sstream>
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

void Server::Session(tcp::socket socket)
{
	//Based on example code from the docs
	std::cout << "Thread Opened" << std::endl;
	asio::streambuf sbuf;
	asio::error_code error;
	std::string clientPrefix = "";
	while (true)
	{
		
		auto mutbuf = sbuf.prepare(1024);
		int msgLen = socket.read_some(mutbuf, error);
		if (error)
		{
			std::cout << "Thread Closed" << std::endl;
			return;
		}
		sbuf.commit(msgLen);
		if (clientPrefix.empty())
		{
			auto conBuf = sbuf.data();
			clientPrefix = std::string(asio::buffers_begin(conBuf),
				asio::buffers_begin(conBuf) + conBuf.size());
			std::cout << "Client Connected with id: " + clientPrefix << std::endl;
		}

		//How to write a string to the client???
		if (sbuf.size() > 0)
		{
			std::cout << "Sending Message To Client: " + clientPrefix << std::endl;
			std::string testStr = "This is a string!";
			//auto testStream = std::stringstream(testStr);
			auto newBuf = asio::buffer(testStr, testStr.length());
			sbuf.prepare(testStr.length());
			//mutbuf = newBuf;
			//sbuf.commit(testStr.length());
			asio::write(socket, newBuf);
		}
		//asio::write(socket, sbuf);
	}
}

void Server::HandleAccept()
{

}

