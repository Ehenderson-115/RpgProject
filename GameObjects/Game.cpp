#include "Game.h"
#include "Player.h"
#include "HelperFunctions.h"


void Game::StartGame()
{
	std::string response;
	std::cout << "Welcome to the Untitled RPG Game. Press Enter to start!" << std::endl;
	std::cin.ignore();

	ParseConfigFile();

}

void Game::ParseConfigFile()
{
	std::fstream configFile;
	std::string line;
	std::string fileStr;
	configFile.open("./Assets/config.txt");
	while (!configFile.eof())
	{
		std::getline(configFile, line);
		fileStr += line;
	}
	configFile.close();

	//Strips Tab Characters
	StripString(fileStr, "\t");
	ParseTag(fileStr);

	std::cin.ignore();
}

void Game::ParseTag(std::string &input)
{
	//TODO Fix Base Case
	std::string objType = "";
	int tagStart = input.find_first_of("<");
	int openTagEnd = input.find_first_of(">");

	//+1 to include the > character
	objType = input.substr(tagStart,( openTagEnd + 1));
	PrintString(objType);
	ParseTag(input.substr(openTagEnd));

	if(openTagEnd == input.find_last_of(">"))
	{
		return;
	}

}

void Game::CreatePlayer()
{
	
}
