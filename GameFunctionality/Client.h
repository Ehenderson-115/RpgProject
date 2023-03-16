#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include "Game.h"

class Client
{
public:
	void InitClient();

private:
	void LogicLoop();
	std::string GetCommandFromUser();
};
#endif