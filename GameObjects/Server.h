#ifndef SERVER_H
#define SERVER_H
#include "../ThirdPartyLibraries/asio-1.24.0/include/asio.hpp"
#include <memory>

class Server 
{
public:
	Server(asio::io_context& io);
	void OpenConnection();

private:
	void StartAccept();
	void HandleAccept();
	asio::io_context* ioContext;
	std::shared_ptr<asio::ip::tcp::acceptor> acceptor;

};

#endif