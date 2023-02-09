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
	std::cout << inStr << std::endl;
}

void StrToLower(std::string& inStr)
{
	for (int i = 0; i < inStr.length(); i++)
	{
		inStr.at(i) = std::tolower(inStr.at(i));
	}
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

