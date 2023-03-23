#include <string>

std::string StripString(std::string inStr, const std::string& stripStr);
void FormattedPrint(std::string inStr);
std::string AddLineBreaks(std::string inStr);
std::string StrToLower(std::string inStr);
std::string RemoveExtraSpaces(std::string inStr);
std::string GrabNextArg(std::string& inStr, bool removeArg = true);
std::string GetPortFromConfigFile(const std::string& filePath);
std::string GetHostnameFromConfigFile(const std::string& filePath);
unsigned short StringToValidPort(std::string strPort);
std::string FormatCommand(std::string inStr);