#include "NetworkFunctions.h"
#include "HelperFunctions.h"
#include "Game.h"
#include <fstream>
#include <mutex>
using asio::ip::tcp;


void AcceptClientConnections(unsigned short port, std::shared_ptr<Game>& gameInstance)
{
	asio::io_context io;
	tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), port));
	io.run();
	while (true)
	{
		std::make_shared<std::thread>(Session, acceptor.accept(), gameInstance)->detach();
	}
}

void Session(tcp::socket socket, std::shared_ptr<Game>& gameInstance)
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

std::string ReadStringFromSocket(const asio::ip::tcp::socket& inSocket, asio::error_code& error)
{
	asio::streambuf sbuf;
}

std::string WriteStringToSocket(const asio::ip::tcp::socket& inSocket)
{
	return std::string();
}

std::string GetPortFromConfigFile(std::string filePath)
{
	std::fstream configFile;
	std::string line;
	std::string fileStr;
	configFile.open(filePath);
	while (!configFile.eof())
	{
		configFile >> line;
		line = StrToLower(line);
		if (line.find("port:") == -1)
		{
			line.clear();
		}
		else
		{
			line = StripString(line, "port:");
			break;

		}
	}
	configFile.close();

	return line;
}

std::string GetHostnameFromConfigFile(std::string filePath)
{
	std::fstream configFile;
	std::string line;
	std::string fileStr;
	configFile.open(filePath);
	while (!configFile.eof())
	{
		configFile >> line;
		line = StrToLower(line);
		if (line.find("hostname:") == -1)
		{
			line.clear();
		}
		else
		{
			line = StripString(line, "hostname:");
			break;

		}
	}
	configFile.close();

	return line;
}

unsigned short StringToValidPort(std::string strPort)
{
	while (true)
	{
		strPort = StripString(strPort, "\n");
		strPort = StripString(strPort, "\t");
		strPort = StripString(strPort, "\r");
		strPort = StripString(strPort, " ");
		if (strPort.length() > 0 && strPort.length() <= 5 && std::numeric_limits<unsigned short>::max() >= std::stoi(strPort))
		{
			return (unsigned short)std::stoi(strPort);
		}
		FormattedPrint(("Error: " + strPort + " is not a valid port"));
	}
}