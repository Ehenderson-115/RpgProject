#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include "../ThirdPartyLibraries/asio-1.24.0/include/asio.hpp"

class Client
{
public:
	Client(asio::io_context& io);
	void ConnectToServer();
	void GetUserCommand();
	
private:
	asio::io_context& mIo;
	asio::ip::tcp::socket mSocket;
	asio::ip::tcp::resolver mResolver;
};
#endif