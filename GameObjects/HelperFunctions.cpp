#include "HelperFunctions.h"

std::string StripString(std::string inStr, const std::string& stripStr)
{
	for (int i = 0; i < inStr.length(); i++)
	{
		if (inStr.substr(i, stripStr.length()) == stripStr)
		{
			inStr.replace(i, stripStr.length(), "");
			i -= stripStr.length();
		}
	}
	return inStr;
}


void PrintString(const std::string& inStr)
{
	std::cout << inStr << std::endl;
}

std::string StrToLower(std::string inStr)
{
	for (int i = 0; i < inStr.length(); i++)
	{
		inStr.at(i) = std::tolower(inStr.at(i));
	}
	return inStr;
}

void GrabAllWords(std::string inStr, std::vector<std::string>& inVect)
{
	int StartOfWord = 0;
	int EndOfWord = inStr.find(" ");
	for (int i = 0; i < inStr.length(); i++)
	{
		inVect.push_back(inStr.substr(StartOfWord, EndOfWord));
		StartOfWord = EndOfWord;
		inStr = inStr.substr(StartOfWord, inStr.length());
		EndOfWord = inStr.find(" ");
		if (i % 100 == 0) {
			inVect.push_back("\n");
		}
	}
}

std::string RemoveExtraSpaces(std::string inStr)
{
	for (int i = 0; i < inStr.length(); i++)
	{
		if (inStr.at(i) == ' ' && !std::isalpha(inStr.at(i + 1)))
		{
			inStr.erase(i, 1);
			i--;

		}
	}
	return inStr;
}

