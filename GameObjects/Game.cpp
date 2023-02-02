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

void Game::ConsumeTypeTag(ObjectType &obj, std::string &dataSource)
{
	int tagStart = dataSource.find("<");
	int tagEnd = dataSource.find(">");
	tagEnd++;
	std::string tag = dataSource.substr(tagStart, tagEnd);
	StrToLower(tag);
	TagToObjType(tag, obj);
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
	ParseFileData(fileStr);

	PrintString("End Of File Reached");
	std::getline(std::cin, response);
}

void Game::ParseFileData(std::string &dataSource)
{
	ObjectType obj = ObjectType::Empty;
	std::string tag = "";
	int startOfTags = dataSource.find_first_of(">");
	int endOfTags = dataSource.find_last_of(">");

	while (startOfTags != endOfTags)
	{
		ConsumeTypeTag(obj, dataSource);
		dataSource = dataSource.substr(startOfTags + size_t(1), endOfTags);

		LoadObject(obj, dataSource);
		obj = ObjectType::Empty;

		//Cuts off everthing after the main tag is processed (Might remove later???)
		dataSource = dataSource.substr(startOfTags + size_t(1), endOfTags);

		startOfTags = dataSource.find_first_of(">");
		endOfTags = dataSource.find_last_of(">");
	}
}

void Game::LoadObject(ObjectType obj, std::string &dataSource)
{
	switch (obj)
	{
	case ObjectType::Player:
		CreatePlayer(dataSource);
		break;
	case ObjectType::Character:
		CreateCharacter(dataSource);
		break;
	case ObjectType::Enemy:
		CreateEnemy(dataSource);
		break;
	case ObjectType::Entity:
		CreateEntity(dataSource);
		break;
	case ObjectType::Weapon:
		CreateWeapon(dataSource);
		break;
	case ObjectType::Item:
		CreateItem(dataSource);
		break;
	case ObjectType::Room:
		CreateRoom(dataSource);
		break;
	default:
		break;
	}

}

void Game::TagToObjType(std::string tag, ObjectType &inObj)
{
	if (tag == "<player>")
	{
		inObj = ObjectType::Player;
	}
	else if (tag == "<character>")
	{
		inObj = ObjectType::Character;
	}
	else if (tag == "<entity>")
	{
		inObj = ObjectType::Entity;
	}
	else if (tag == "<weapon>")
	{
		inObj = ObjectType::Weapon;
	}
	else if (tag == "<enemy>")
	{
		inObj = ObjectType::Enemy;
	}
	else if (tag == "<item>")
	{
		inObj = ObjectType::Item;
	}
	else if (tag == "<room>")
	{
		inObj = ObjectType::Room;
	}
	else
	{
		inObj = ObjectType::Empty;
	}
}

void Game::FindObjEndTag(ObjectType obj, std::string dataSource)
{
	switch (obj)
	{
	case ObjectType::Player:
		CreatePlayer(dataSource);
		break;
	case ObjectType::Character:
		CreateCharacter(dataSource);
		break;
	case ObjectType::Enemy:
		CreateEnemy(dataSource);
		break;
	case ObjectType::Entity:
		CreateEntity(dataSource);
		break;
	case ObjectType::Weapon:
		CreateWeapon(dataSource);
		break;
	case ObjectType::Item:
		CreateItem(dataSource);
		break;
	case ObjectType::Room:
		CreateRoom(dataSource);
		break;
	default:
		break;
	}

}

void Game::CreatePlayer(std::string& datasource)
{
	DataType dataT = DataType::Empty;



}

void Game::CreateRoom(std::string& dataSource)
{
}

void Game::CreateEnemy(std::string& dataSource)
{
}

void Game::CreateItem(std::string& dataSource)
{
}

void Game::CreateCharacter(std::string& dataSource)
{
}

void Game::CreateEntity(std::string& dataSource)
{
}

void Game::CreateWeapon(std::string& dataSource)
{
}