#include "HelperFunctions.h"

void StripString(std::string &input, std::string stripStr)
{
	for (int i = 0; i < input.length(); i++) 
	{
		if (input.substr(i, stripStr.length()) == stripStr)
		{
			input.replace(i, stripStr.length(), "");
		}
	}

}

void PrintString(std::string input)
{
	std::cout << input << std::endl;
}
