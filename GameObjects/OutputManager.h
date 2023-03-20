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
	void AppendToOutput(const std::string& inStr);
	void PrintScreen();
	void StatusBar(const std::string& inStr) { mStatusBar = inStr; };
	void Output(const std::string& inStr) { mOutput = inStr; };
	std::string StatusBar() const { return mStatusBar; };
	std::string Output() const { return mOutput; };

private:
	std::string mOutput;
	std::string mStatusBar;





};


#endif