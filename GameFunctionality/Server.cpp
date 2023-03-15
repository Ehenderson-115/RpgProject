#include "Server.h"
#include "HelperFunctions.h"
#include <thread>
using asio::ip::tcp;

Server::Server()
	: mIo()
	, mPort(StringToValidPort(GetPortFromConfigFile("./Assets/NetworkConfig.txt")))
	, mAcceptor(mIo, tcp::endpoint(tcp::v4(), mPort))
{}

void Server::InitServer()
{
	FormattedPrint("Hosting Server on port " + std::to_string(mPort));
	CheckForNewClients();
}


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
	FormattedPrint("New Client Connected");
	asio::streambuf sbuf;
	asio::error_code error;
	std::string clientPrefix = "";
	while (true)
	{
		
		auto mutbuf = sbuf.prepare(1024);
		int msgLen = socket.read_some(mutbuf, error);
		if (error)
		{
			FormattedPrint("Connection to client closed due to: " + error.message());
			return;
		}
		sbuf.commit(msgLen);
		if (clientPrefix.empty())
		{
			auto conBuf = sbuf.data();
			clientPrefix = std::string(asio::buffers_begin(conBuf),
				asio::buffers_begin(conBuf) + conBuf.size());
			FormattedPrint("Client Connected with id: " + clientPrefix);
		}
		sbuf.consume(1024);
		if (sbuf.size() > 0)
		{
			FormattedPrint("Sending Message To Client: " + clientPrefix);
			std::string testStr = "This is a string!";
			auto newBuf = asio::buffer(testStr, testStr.length());
			asio::write(socket, newBuf);
		}
	}
}

void Server::HandleAccept()
{

}

