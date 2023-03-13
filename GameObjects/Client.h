#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include "asio.hpp"

class Client
{
public:
	Client();
	void InitServerConnection();

	
private:
	void ActiveConnectionLoop();
	std::string GetCommandFromUser();
	asio::io_context mIo;
	asio::ip::tcp::socket mSocket;
	asio::ip::tcp::resolver mResolver;
	unsigned short mPort;
};
#endif