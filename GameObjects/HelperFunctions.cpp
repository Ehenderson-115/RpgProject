#include "HelperFunctions.h"
#include <iostream>
#include <fstream>
#include <limits>


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

void FormattedPrint(std::string inStr)
{
	inStr = AddLineBreaks(inStr);
	std::cout << inStr << std::endl;
}

std::string AddLineBreaks(std::string inStr)
{
	bool noLineBreaks = true;
	std::string output = "";
	if (inStr.length() >= 100)
	{
		int breakPoint = inStr.substr(0, 100).find_last_of(" ");
		for (auto character : inStr.substr(0, 100))
		{
			if (character == '\n')
			{
				noLineBreaks = false;
			}
		}
		if (noLineBreaks)
		{
			inStr.erase(breakPoint, 1);
			inStr.insert(breakPoint, "\n");
		}
		output += inStr.substr(0, 100);
		output += AddLineBreaks(inStr.substr(100));
	}
	else
	{
		output = inStr;
		return output;
	}
	return output;
}

std::string StrToLower(std::string inStr)
{
	for (int i = 0; i < inStr.length(); i++)
	{
		inStr.at(i) = std::tolower(inStr.at(i));
	}
	return inStr;
}


std::string RemoveExtraSpaces(std::string inStr)
{
	for (int i = 0; i < inStr.length(); i++)
	{
		if (i == (inStr.length() - 1) && inStr.at(i) == ' ')
		{
			inStr.erase(i, 1);
		}
		else if (inStr.at(i) == ' ' && !std::isalpha(inStr.at(i + 1)))
		{
			inStr.erase(i, 1);
			i--;
		}
	}
	return inStr;
}

std::string GrabNextArg(std::string& inStr, bool removeArg)
{
	int firstSpace = inStr.find(" ");
	std::string output = inStr.substr(0, firstSpace);
	if (removeArg)
	{
		inStr = inStr.substr(firstSpace + 1);
	}
	return output;
}

std::string GetPortFromConfigFile(const std::string& filePath)
{
	std::fstream configFile;
	std::string line;
	std::string fileStr;
	configFile.open(filePath);
	while (!configFile.eof())
	{
		configFile >> line;
		line = StrToLower(line);
		if (line.find("port:") == -1)
		{
			line.clear();
		}
		else
		{
			line = StripString(line, "port:");
			break;

		}
	}
	configFile.close();

	return line;
}

std::string GetHostnameFromConfigFile(const std::string& filePath)
{
	std::fstream configFile;
	std::string line;
	std::string fileStr;
	configFile.open(filePath);
	while (!configFile.eof())
	{
		configFile >> line;
		line = StrToLower(line);
		if (line.find("hostname:") == -1)
		{
			line.clear();
		}
		else
		{
			line = StripString(line, "hostname:");
			break;

		}
	}
	configFile.close();

	return line;
}

unsigned short StringToValidPort(std::string strPort)
{
	while (true)
	{
		strPort = StripString(strPort, "\n");
		strPort = StripString(strPort, "\t");
		strPort = StripString(strPort, "\r");
		strPort = StripString(strPort, " ");
		if (strPort.length() > 0 && strPort.length() <= 5 && std::numeric_limits<unsigned short>::max() >= std::stoi(strPort))
		{
			return (unsigned short)std::stoi(strPort);
		}
		FormattedPrint(("Error: " + strPort + " is not a valid port"));
	}
}

std::string FormatCommand(std::string inStr)
{
	inStr = StrToLower(inStr);
	inStr = RemoveExtraSpaces(inStr);
	return inStr;
}