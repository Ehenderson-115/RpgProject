#ifndef SERVER_H
#define SERVER_H
#include "../ThirdPartyLibraries/asio-1.24.0/include/asio.hpp"
#include <memory>

class Server 
{
public:
	Server(asio::io_context& io, const short inPort);
	void CheckForNewClients();

private:
	static void Session(asio::ip::tcp::socket socket);
	void HandleAccept();
	asio::io_context& mIo;
	short mPort;
	asio::ip::tcp::acceptor mAcceptor;

};

#endif