#include <string>
#include <iostream>
#include <vector>

std::string StripString(std::string inStr, const std::string& stripStr);
void FormattedPrint(std::string inStr);
std::string AddLineBreaks(std::string inStr);
std::string StrToLower(std::string inStr);
std::string RemoveExtraSpaces(std::string inStr);
std::string GrabNextArg(std::string& inStr, bool removeArg = true);
