#include <string>
#include <iostream>
#include <vector>

std::string StripString(std::string inStr, const std::string& stripStr);
void PrintString(const std::string& inStr);
std::string StrToLower(std::string inStr);
void GrabNextArg(std::string& inStr, std::vector<std::string>& inVect);
void GrabAllWords(std::string inStr, std::vector<std::string>& inVect);
std::string RemoveExtraSpaces(std::string inStr);
