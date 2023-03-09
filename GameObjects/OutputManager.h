#ifndef OUTPUT_MANAGER_H
#define OUTPUT_MANAGER_H
#include <string>
#include <memory>
struct ClientData;

class OutputManager 
{

public:
	OutputManager();
	void UpdateStatusBar(const std::shared_ptr<ClientData>& inData);
	void AddToOutput(const std::string& inStr);
	void PrintScreen();



private:
	std::string mOutput;
	std::string mStatusBar;





};


#endif