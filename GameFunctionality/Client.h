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
	void ParseResultString(std::string inStr);
	std::string ConsumeTag(std::string& inStr);
	void ProcessResult(const std::string& result);
	std::string GetCommandFromUser();
	
	std::shared_ptr<OutputManager> mOutputManager;
	ClientData::GameState mState;

};
#endif