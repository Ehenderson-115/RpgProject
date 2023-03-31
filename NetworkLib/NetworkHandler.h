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
	bool WriteStringToSocket(std::string inStr, int socketId = 0);
	void SafelyCloseSocket(int socketId = 0);

	void ListenForNewClients(unsigned short port);
	static void InitSession(int socketId, NetworkHandler* inHandler);
	virtual void ServerSession(int socketId);

	void ConnectToServer(const std::string& hostname, const std::string& port);

protected:
	static std::mutex mMutex;

private:
	unsigned int mSocketCount;
	std::vector<asio::ip::tcp::socket> mActiveSockets;
	asio::io_context mIo;
	

};

#endif