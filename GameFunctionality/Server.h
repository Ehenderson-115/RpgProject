#ifndef SERVER_H
#define SERVER_H
#include "Game.h"
#include "asio.hpp"
#include <memory>
#include <string>

class Server 
{
public:
	Server();
	void InitServer();
private:
	void CheckForNewClients();
	static void Session(asio::ip::tcp::socket socket);
	void HandleAccept();

	asio::io_context mIo;
	unsigned short mPort;
	asio::ip::tcp::acceptor mAcceptor;
	std::shared_ptr<Game> mGame;

};

#endif