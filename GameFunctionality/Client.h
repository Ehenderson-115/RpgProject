#ifndef CLIENT_H
#define CLIENT_H
#include <string>

class Client
{
public:
	void InitClient();

private:
	std::string GetCommandFromUser();
};
#endif