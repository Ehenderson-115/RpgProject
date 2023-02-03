#include "Game.h"
#include "Player.h"
#include "Room.h"
#include "Entity.h"
#include "Character.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Item.h"
#include "HelperFunctions.h"


void Game::StartGame()
{
	std::string response;
	PrintString("Welcome to the Untitled RPG Game. Press Enter to start!");
	std::getline(std::cin,response);
	ParseConfigFile();

}

std::string Game::FetchTag(std::string& dataSource)
{
	int tagStart = dataSource.find("<");
	int tagEnd = dataSource.find(">");
	tagEnd++;
	return dataSource.substr(tagStart, tagEnd);
}

void Game::StripCurrTag(std::string &dataSource)
{
	int tagStart = dataSource.find("<");
	int tagEnd = dataSource.find(">");
	tagEnd++;
	dataSource = dataSource.substr(tagEnd);
}

void Game::ConsumeObjTag(ObjectType &obj, std::string &dataSource)
{
	std::string tag = FetchTag(dataSource);
	
	UpdateObjType(tag, obj);
	StripCurrTag(dataSource);
	
}

void Game::ConsumeDataTag(DataType &dataType, std::string &dataSource)
{
	std::string tag = FetchTag(dataSource);

	//Ensure the tag is in all lowercase
	UpdateDataType(tag, dataType);

	//Strips off the consumed tag from the source string
	StripCurrTag(dataSource);
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

		ConsumeObjTag(obj, dataSource);
		LoadObject(obj, dataSource);
		StripCurrTag(dataSource);

		obj = ObjectType::Empty;

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

void Game::UpdateObjType(std::string tag, ObjectType &inObj)
{
	StrToLower(tag);
	if (tag == "<inPlayer>")
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

void Game::UpdateDataType(std::string tag, DataType& inDataType)
{
	StrToLower(tag);
	if (tag == "<id>")
	{
		inDataType = DataType::ID;
	}
	else if (tag == "<name>")
	{
		inDataType = DataType::Name;
	}
	else if (tag == "<race>")
	{
		inDataType = DataType::Race;
	}
	else if (tag == "<hitpoints>")
	{
		inDataType = DataType::Hitpoints;
	}
	else if (tag == "<descript>")
	{
		inDataType = DataType::Descript;
	}
	else if (tag == "<damage>")
	{
		inDataType = DataType::Damage;
	}
	else if (tag == "<north>")
	{
		inDataType = DataType::North;
	}
	else if (tag == "<south>")
	{
		inDataType = DataType::South;
	}
	else if (tag == "<east>")
	{
		inDataType = DataType::East;
	}
	else if (tag == "<west>")
	{
		inDataType = DataType::West;
	}
	else
	{
		inDataType = DataType::Empty;
	}
}

void Game::CreatePlayer(std::string &dataSource)
{
	Player newPlayer = Player();
	std::string nextTag = FetchTag(dataSource);
	DataType dataType = DataType::Empty;
	UpdateDataType(nextTag, dataType);
	StripCurrTag(dataSource);

	while (dataType != DataType::Empty)
	{
		//ConsumeDataTag(dataType, dataSource);
		SetPlayerData(dataType, dataSource, newPlayer);
		StripCurrTag(dataSource);

		nextTag = FetchTag(dataSource);
		UpdateDataType(nextTag, dataType);
		StripCurrTag(dataSource);
	}



	mGameEntities.push_back(std::make_shared<Entity>(newPlayer));
}

void Game::SetPlayerData(DataType dataType, std::string& dataSource, Player& inPlayer)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inPlayer.SetId(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inPlayer.SetName(dataToAdd);
		break;
	case DataType::Race:
		inPlayer.SetRace(dataToAdd);
		break;
	case DataType::Hitpoints:
		inPlayer.SetHitpoints(dataToAdd);
		break;
	}
}

void Game::CreateRoom(std::string& dataSource)
{
	Room newRoom = Room();
	std::string nextTag = FetchTag(dataSource);
	DataType dataType = DataType::Empty;
	UpdateDataType(nextTag, dataType);
	StripCurrTag(dataSource);

	while (dataType != DataType::Empty)
	{
		//ConsumeDataTag(dataType, dataSource);
		SetRoomData(dataType, dataSource, newRoom);
		StripCurrTag(dataSource);

		nextTag = FetchTag(dataSource);
		UpdateDataType(nextTag, dataType);
		StripCurrTag(dataSource);
	}



	mGameEntities.push_back(std::make_shared<Entity>(newRoom));
}

void Game::SetRoomData(DataType dataType, std::string& dataSource, Room& inRoom)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inRoom.SetId(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inRoom.SetName(dataToAdd);
		break;
	case DataType::Descript:
		inRoom.SetDescript(dataToAdd);
		break;
	case DataType::North:
		inRoom.AddRoomConnection(std::stoi(dataToAdd), 'n');
		break;
	case DataType::South:
		inRoom.AddRoomConnection(std::stoi(dataToAdd), 's');
		break;
	case DataType::East:
		inRoom.AddRoomConnection(std::stoi(dataToAdd), 'e');
		break;
	case DataType::West:
		inRoom.AddRoomConnection(std::stoi(dataToAdd), 'w');
		break;
	//TODO ADD CONTENTS CASE
	}

}

void Game::CreateEnemy(std::string& dataSource)
{
	Enemy newEnemy = Enemy();
	std::string nextTag = FetchTag(dataSource);
	DataType dataType = DataType::Empty;
	UpdateDataType(nextTag, dataType);
	StripCurrTag(dataSource);

	while (dataType != DataType::Empty)
	{
		SetEnemyData(dataType, dataSource, newEnemy);
		StripCurrTag(dataSource);

		nextTag = FetchTag(dataSource);
		UpdateDataType(nextTag, dataType);
		StripCurrTag(dataSource);
	}



	mGameEntities.push_back(std::make_shared<Entity>(newEnemy));
}

void Game::SetEnemyData(DataType dataType, std::string& dataSource, Enemy& inEnemy)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inEnemy.SetId(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inEnemy.SetName(dataToAdd);
		break;
	case DataType::Race:
		inEnemy.SetRace(dataToAdd);
		break;
	case DataType::Hitpoints:
		inEnemy.SetHitpoints(dataToAdd);
		break;
	}
}

void Game::CreateItem(std::string& dataSource)
{
	Item newItem = Item();
	std::string nextTag = FetchTag(dataSource);
	DataType dataType = DataType::Empty;
	UpdateDataType(nextTag, dataType);
	StripCurrTag(dataSource);

	while (dataType != DataType::Empty)
	{
		SetItemData(dataType, dataSource, newItem);
		StripCurrTag(dataSource);

		nextTag = FetchTag(dataSource);
		UpdateDataType(nextTag, dataType);
		StripCurrTag(dataSource);
	}



	mGameEntities.push_back(std::make_shared<Entity>(newItem));
}

void Game::SetItemData(DataType dataType, std::string& dataSource, Item& inItem)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inItem.SetId(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inItem.SetName(dataToAdd);
		break;
	case DataType::Descript:
		inItem.SetDescript(dataToAdd);
		break;
	}
}

void Game::CreateCharacter(std::string& dataSource)
{
	Character newCharacter = Character();
	std::string nextTag = FetchTag(dataSource);
	DataType dataType = DataType::Empty;
	UpdateDataType(nextTag, dataType);
	StripCurrTag(dataSource);

	while (dataType != DataType::Empty)
	{
		SetCharacterData(dataType, dataSource, newCharacter);
		StripCurrTag(dataSource);

		nextTag = FetchTag(dataSource);
		UpdateDataType(nextTag, dataType);
		StripCurrTag(dataSource);
	}



	mGameEntities.push_back(std::make_shared<Entity>(newCharacter));
}

void Game::SetCharacterData(DataType dataType, std::string& dataSource, Character& inCharacter)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inCharacter.SetId(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inCharacter.SetName(dataToAdd);
		break;
	case DataType::Race:
		inCharacter.SetRace(dataToAdd);
		break;
	case DataType::Hitpoints:
		inCharacter.SetHitpoints(dataToAdd);
		break;
	}
}

void Game::CreateEntity(std::string& dataSource)
{
	Entity newEntity = Entity();
	std::string nextTag = FetchTag(dataSource);
	DataType dataType = DataType::Empty;
	UpdateDataType(nextTag, dataType);
	StripCurrTag(dataSource);

	while (dataType != DataType::Empty)
	{
		SetEntityData(dataType, dataSource, newEntity);
		StripCurrTag(dataSource);

		nextTag = FetchTag(dataSource);
		UpdateDataType(nextTag, dataType);
		StripCurrTag(dataSource);
	}
	mGameEntities.push_back(std::make_shared<Entity>(newEntity));
}

void Game::SetEntityData(DataType dataType, std::string& dataSource, Entity& inEntity)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inEntity.SetId(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inEntity.SetName(dataToAdd);
		break;
	case DataType::Descript:
		inEntity.SetDescript(dataToAdd);
		break;
	}
}

void Game::CreateWeapon(std::string& dataSource)
{
	Weapon newWeapon = Weapon();
	std::string nextTag = FetchTag(dataSource);
	DataType dataType = DataType::Empty;
	UpdateDataType(nextTag, dataType);
	StripCurrTag(dataSource);

	while (dataType != DataType::Empty)
	{
		SetWeaponData(dataType, dataSource, newWeapon);
		StripCurrTag(dataSource);

		nextTag = FetchTag(dataSource);
		UpdateDataType(nextTag, dataType);
		StripCurrTag(dataSource);
	}



	mGameEntities.push_back(std::make_shared<Entity>(newWeapon));
}

void Game::SetWeaponData(DataType dataType, std::string& dataSource, Weapon& inWeapon)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inWeapon.SetId(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inWeapon.SetName(dataToAdd);
		break;
	case DataType::Descript:
		inWeapon.SetDescript(dataToAdd);
		break;
	case DataType::Damage:
		inWeapon.SetDamage(std::stoi(dataToAdd));
		break;
	}
}