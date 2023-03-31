#ifndef SERVER_H
#define SERVER_H
#include "NetworkHandler.h"
#include "Game.h"
#include <memory>
#include <string>

class Server : public NetworkHandler
{
public:
	void InitServer();
private:
	
	void ServerSession(int socketId);
	std::string AddClientToGame(int socketId);
	std::shared_ptr<Game> mGame;

};

#endif