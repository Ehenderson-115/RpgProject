#define TESTING
#ifdef TESTING

#include "Server.h"

#endif 

#ifndef TESTING

#include "Game.h"

#endif 


int main(int argc, char* argv[])
{
	#ifndef TESTING
	Game myGame;
	myGame.InitServer();
	#endif
	#ifdef TESTING
	asio::io_context io;
	short port = 13;
	Server myServer(io,port);
	myServer.CheckForNewClients();
	#endif 

  return 0;
}