#include "NetworkHandler.h"
#include "HelperFunctions.h"
#include <iostream>
#include <thread>
#include "NetworkHandler.h"


using asio::ip::tcp;

NetworkHandler::NetworkHandler()
	: mSocketCount{ 0 }
{
}

std::string NetworkHandler::ReadStringFromSocket(int socketId)
{
	asio::streambuf sbuf;
	asio::error_code error;
	std::string output = "";
	auto mutbuf = sbuf.prepare(1024);
	int msgLen = mOpenSockets.at(socketId).read_some(mutbuf, error);
	if (error)
	{
		FormattedPrint("Failed to read message from socket: " + error.message());
	}
	else
	{
		sbuf.commit(msgLen);
		auto conBuf = sbuf.data();
		output = std::string(asio::buffers_begin(conBuf),
		asio::buffers_begin(conBuf) + conBuf.size());
	}
	return output;
}

void NetworkHandler::WriteStringToSocket(std::string inStr, int socketId)
{

	const int MAX_RETRY_COUNT = 5;
	
	asio::error_code error;
	auto buf = asio::buffer(inStr, inStr.length());
	for (int i = 0; i < MAX_RETRY_COUNT; i++)
	{
		asio::write(mOpenSockets.at(socketId), buf, error);
		if (error)
		{
			FormattedPrint("Falied to write message to socket: " + error.message());
			FormattedPrint("Retrying...");

		}
		else
		{
			break;
		}
	}
}

void NetworkHandler::ListenForNewClients(unsigned short port)
{
	int socketId = 0;
	tcp::acceptor acceptor(mIo, tcp::endpoint(tcp::v4(), port));
	mIo.run();

	while (true)
	{
		mOpenSockets.push_back(acceptor.accept());
		std::make_shared<std::thread>(ServerSession, socketId)->detach();
		socketId++;
	}
}

void NetworkHandler::ServerSession(int socketId)
{
	FormattedPrint("Session Created");
}

void NetworkHandler::ConnectToServer(const std::string& hostname, const std::string& port)
{
	mOpenSockets.push_back(tcp::socket(mIo));
	tcp::resolver resolver(mIo);
	asio::error_code error;

	FormattedPrint("Attempting to connect to Server " + hostname + " on port " + port);
	asio::connect(mOpenSockets.at(0), resolver.resolve(hostname, port), error);
	if (error)
	{
		FormattedPrint("Unable to connect to server due to: " + error.message());
	}
	else
	{
		FormattedPrint("Connection made!");
		mIo.run();
	}

}

void NetworkHandler::ClientSession(std::string& result, std::string& command)
{
	
}

