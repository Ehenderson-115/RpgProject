#ifndef SERVER_H
#define SERVER_H
#include "Game.h"
#include <memory>
#include <string>

class Server 
{
public:
	void InitServer();
private:
	void CheckForNewClients();

	std::shared_ptr<Game> mGame;

};

#endif