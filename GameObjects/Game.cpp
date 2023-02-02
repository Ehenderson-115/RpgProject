#include "Game.h"
#include "Player.h"
#include "HelperFunctions.h"


void Game::StartGame()
{
	std::string response;
	PrintString("Welcome to the Untitled RPG Game. Press Enter to start!");
	std::getline(std::cin,response);
	ParseConfigFile();

}

void Game::ParseConfigFile()
{
	std::string response;
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

	PrintString("End Of File Reached");
	std::getline(std::cin, response);
}

void Game::ParseTag(std::string &input)
{
	std::string objType = "";
	int tagStart = input.find("<");
	int tagEnd = input.find(">");
	int endOfTags = input.find_last_of(">");

	while (tagEnd != endOfTags)
	{
		if (objType == "")
		{
			objType = input.substr(tagStart + size_t(1), tagEnd - size_t(1));
			PrintString(objType);
		}
		input = input.substr(tagEnd, endOfTags);

		tagEnd = input.find(">");
	}

	PrintString(objType);
	

}

void Game::CreatePlayer()
{
	
}
