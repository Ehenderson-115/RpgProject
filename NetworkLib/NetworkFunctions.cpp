#include "NetworkFunctions.h"
#include "HelperFunctions.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <mutex>
using asio::ip::tcp;


std::string ReadStringFromSocket(asio::ip::tcp::socket& inSocket)
{
	asio::streambuf sbuf;
	asio::error_code error;
	std::string output = "";
	auto mutbuf = sbuf.prepare(1024);
	int msgLen = inSocket.read_some(mutbuf, error);
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

void WriteStringToSocket(asio::ip::tcp::socket& inSocket, std::string inStr)
{
	//Convert to CMake define?
	const int MAX_RETRY_COUNT = 5;
	
	asio::error_code error;
	auto buf = asio::buffer(inStr, inStr.length());
	for (int i = 0; i < MAX_RETRY_COUNT; i++)
	{
		asio::write(inSocket, buf, error);
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

std::string GetPortFromConfigFile(const std::string& filePath)
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

std::string GetHostnameFromConfigFile(const std::string& filePath)
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

std::string FormatCommand(std::string inStr)
{
	inStr = StrToLower(inStr);
	inStr = RemoveExtraSpaces(inStr);
	return inStr;
}

void AcceptClientConnections(unsigned short port, std::shared_ptr<Game>& gameInstance)
{
	asio::io_context io;
	tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), port));
	io.run();
	while (true)
	{
		std::make_shared<std::thread>(ServerSession, acceptor.accept(), gameInstance)->detach();
	}
}

void ServerSession(tcp::socket socket, std::shared_ptr<Game>& gameInstance)
{
	//Based on example code from the docs
	FormattedPrint("New Client Connected");
	asio::streambuf sbuf;
	asio::error_code error;
	std::string clientName = AddClientToGame(socket, gameInstance);
	std::string clientCommand = "";
	std::string clientStatus = "";
	while (true)
	{
		//Waits for command to come in
		clientCommand = FormatCommand(ReadStringFromSocket(socket));
		clientStatus = gameInstance->ExecuteCommand(clientName, clientCommand);

		//Updates the client with the status of their character
		WriteStringToSocket(socket, clientStatus);
	}
}

std::string AddClientToGame(tcp::socket& inSocket, std::shared_ptr<Game>& gameInstance)
{
	bool isValidName = false;
	WriteStringToSocket(inSocket, "Please enter the name of your character");
	std::string clientName = ReadStringFromSocket(inSocket);
	isValidName = gameInstance->AddNewPlayer(clientName);
	while(!isValidName)
	{ 
		WriteStringToSocket(inSocket, "The name you provided is already being used by another player, please enter a new one");
		clientName = ReadStringFromSocket(inSocket);
		isValidName = gameInstance->AddNewPlayer(clientName);	
	}
	WriteStringToSocket(inSocket, "You have been successfully added to the game world!");
	return clientName;
}


tcp::socket InitServerConnection(asio::io_context& io)
{
	tcp::socket socket(io);
	tcp::resolver resolver(io);
	asio::error_code error;

	std::string hostname = GetHostnameFromConfigFile("./ConfigFiles/NetworkConfig.txt");
	std::string port = GetPortFromConfigFile("./ConfigFiles/NetworkConfig.txt");

	FormattedPrint("Attempting to connect to Server " + hostname + " on port " + port);
	asio::connect(socket, resolver.resolve(hostname, port), error);
	FormattedPrint("Connection made!");

	return socket;
}

void ClientSession(std::string& result, std::string& command)
{
	asio::io_context io;
	tcp::socket socket = InitServerConnection(io);
	io.run();
	result = ReadStringFromSocket(socket);


	while (true)
	{
		if (result.empty() && !command.empty())
		{
			WriteStringToSocket(socket, command);
			result = ReadStringFromSocket(socket);
			command.clear();
		}
	}
}

