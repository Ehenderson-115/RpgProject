#include "Game.h"
#include "Player.h"


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
	std::string word;
	configFile.open("config.txt");
	std::getline(configFile, word);
	std::cout << std::endl;
	std::cin.ignore();


	configFile.close();
}

void Game::CreatePlayer()
{
	
}
