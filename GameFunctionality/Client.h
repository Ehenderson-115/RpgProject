#ifndef CLIENT_H
#define CLIENT_H
#include <memory>
#include <string>
#include <mutex>
#include "OutputManager.h"
#include "ClientData.h"

class Client
{
public:
	void Start();
	
private:
	std::string GetCommandFromUser();
	std::shared_ptr<OutputManager> mOutputManager;
};
#endif