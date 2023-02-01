#include "HelperFunctions.h"

void StripString(std::string &input, std::string stripChar)
{
	for (int i = 0; i < input.length(); i++) 
	{
		if (input.substr(i, 1) == stripChar)
		{
			input.replace(i, 1, "");
		}
	}

}

void PrintString(std::string input)
{
	std::cout << input << std::endl;
}
