#include "HelperFunctions.h"

void StripString(std::string& inStr, std::string stripStr)
{
	for (int i = 0; i < inStr.length(); i++)
	{
		if (inStr.substr(i, stripStr.length()) == stripStr)
		{
			inStr.replace(i, stripStr.length(), "");
			i -= stripStr.length();
		}
	}

}


void PrintString(const std::string& inStr)
{
	std::cout << inStr << std::endl << std::endl;
}

void StrToLower(std::string& inStr)
{
	for (int i = 0; i < inStr.length(); i++)
	{
		inStr.at(i) = std::tolower(inStr.at(i));
	}
}

void GrabNextWord(std::string& inStr, std::vector<std::string>& inVect)
{
	int firstSpace = inStr.find(" ");
	inVect.push_back(inStr.substr(0, firstSpace));
	inStr = inStr.substr(firstSpace + 1);

}

void RemoveExtraSpaces(std::string& inStr)
{
	for (int i = 0; i < inStr.length(); i++)
	{
		if (inStr.at(i) == ' ' && !std::isalpha(inStr.at(i + 1)))
		{
			inStr.erase(i, 1);
			i--;

		}
	}
}

