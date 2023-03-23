#ifndef CLIENT_H
#define CLIENT_H
#include <memory>
#include <string>
#include <mutex>
#include "NetworkHandler.h"
#include "OutputManager.h"
#include "ClientData.h"

class Client : public NetworkHandler
{
public:
	void InitClient();
	
private:
	void MainLoop();
	std::string GetCommandFromUser();
	std::shared_ptr<OutputManager> mOutputManager;


};
#endif