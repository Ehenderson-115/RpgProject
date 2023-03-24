#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H
#include "asio.hpp"
#include <string>
#include <memory>
#include <mutex>
#include <vector>
 
class NetworkHandler
{

public:
	NetworkHandler();
	//Helper methods
	std::string ReadStringFromSocket(int socketId = 0);
	void WriteStringToSocket(std::string inStr, int socketId = 0);


	void ListenForNewClients(unsigned short port);
	static void InitSession(int socketId, NetworkHandler* inHandler);
	virtual void ServerSession(int socketId);

	void ConnectToServer(const std::string& hostname, const std::string& port);
	void ClientSession(std::string& result, std::string& command);
protected:
	static std::mutex mMutex;

private:
	unsigned int mSocketCount;
	std::vector<asio::ip::tcp::socket> mOpenSockets;
	asio::io_context mIo;
	

};

#endif