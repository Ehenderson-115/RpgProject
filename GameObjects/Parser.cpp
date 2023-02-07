#include "Parser.h"
#include "Player.h"
#include "Room.h"
#include "Entity.h"
#include "Character.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Item.h"
#include "HelperFunctions.h"

std::string Parser::FetchTag()
{
	int tagStart = dataSource.find("<");
	int tagEnd = dataSource.find(">");
	tagEnd++;
	std::string outputStr = dataSource.substr(tagStart, tagEnd);
	StrToLower(outputStr);
	return outputStr;
}

void Parser::StripCurrTag()
{
	int tagStart = dataSource.find("<");
	int tagEnd = dataSource.find(">");
	tagEnd++;
	dataSource = dataSource.substr(tagEnd);
}


void Parser::ConsumeObjTag(ObjectType& obj)
{
	std::string tag = FetchTag();
	StrToObjType(tag, obj);

	//Strips off the consumed tag from the source string
	StripCurrTag();

}

void Parser::ConsumeDataTag(DataType& dataType)
{
	std::string tag = FetchTag();
	StrToDataType(tag, dataType);

	//Strips off the consumed tag from the source string
	StripCurrTag();
}

std::vector<std::shared_ptr<Entity>> Parser::ParseConfigFile(const std::string& fileToParse)
{
	std::string response;
	std::fstream configFile;
	std::string line;
	std::string fileStr;
	configFile.open(fileToParse);
	while (!configFile.eof())
	{
		std::getline(configFile, line);
		fileStr += line;
	}
	configFile.close();

	//Strips Tab Characters

	StripString(fileStr, "\t");
	dataSource = fileStr;
	ParseFileData();
	return mParsedEntites;
}

void Parser::ParseFileData()
{
	ObjectType obj = ObjectType::Empty;
	std::string tag = "";
	int startOfTags = dataSource.find_first_of(">");
	int endOfTags = dataSource.find_last_of(">");

	while (startOfTags != endOfTags)
	{

		ConsumeObjTag(obj);
		LoadObject(obj);

		obj = ObjectType::Empty;

		startOfTags = dataSource.find_first_of(">");
		endOfTags = dataSource.find_last_of(">");
	}
}

void Parser::LoadObject(ObjectType obj)
{
	switch (obj)
	{
	case ObjectType::Player:
		CreatePlayer();
		break;
	case ObjectType::Character:
		CreateCharacter();
		break;
	case ObjectType::Enemy:
		CreateEnemy();
		break;
	case ObjectType::Entity:
		CreateEntity();
		break;
	case ObjectType::Weapon:
		CreateWeapon();
		break;
	case ObjectType::Item:
		CreateItem();
		break;
	case ObjectType::Room:
		CreateRoom();
		break;
	default:
		break;
	}

}

void Parser::StrToObjType(std::string tag, ObjectType& inObj)
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

void Parser::StrToDataType(std::string tag, DataType& inDataType)
{
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
	else if (tag == "<contents>")
	{
		inDataType = DataType::Contents;
	}
	else
	{
		inDataType = DataType::Empty;
	}
}

void Parser::CreatePlayer()
{
	Player newPlayer = Player();
	std::string nextTag = FetchTag();
	DataType dataType = DataType::Empty;
	StrToDataType(nextTag, dataType);
	StripCurrTag();

	while (dataType != DataType::Empty)
	{
		SetPlayerData(dataType, newPlayer);
		StripCurrTag();

		nextTag = FetchTag();
		StrToDataType(nextTag, dataType);
		StripCurrTag();
	}

	mParsedEntites.push_back(std::make_shared<Player>(newPlayer));
}

void Parser::SetPlayerData(DataType dataType, Player& inPlayer)
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

void Parser::CreateRoom()
{
	Room newRoom = Room();
	std::string nextTag = FetchTag();
	DataType dataType = DataType::Empty;
	StrToDataType(nextTag, dataType);
	StripCurrTag();

	while (dataType != DataType::Empty)
	{
		SetRoomData(dataType, newRoom);
		StripCurrTag();

		nextTag = FetchTag();
		StrToDataType(nextTag, dataType);
		StripCurrTag();
	}

	mParsedEntites.push_back(std::make_shared<Room>(newRoom));
}

void Parser::SetRoomData(DataType dataType, Room& inRoom)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	DataType contentType = DataType::Empty;
	ObjectType contentObjType = ObjectType::Empty;
	std::string currTag = "";
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
	case DataType::Contents:
		currTag = FetchTag();
		while (currTag != "</contents>")
		{
			StrToObjType(currTag, contentObjType);
			StripCurrTag();
			dataToAdd = dataSource.substr(0, dataSource.find("<"));
			std::shared_ptr<Player> roomPlayer = nullptr;
			switch (contentObjType)
			{
			case ObjectType::Player:
				roomPlayer = std::static_pointer_cast<Player>(mParsedEntites.at(std::stoi(dataToAdd)));
				roomPlayer->SetCurrRoomId(inRoom.GetId());
				break;
			case ObjectType::Character:
				inRoom.AddRoomObject(mParsedEntites.at(std::stoi(dataToAdd)));
				break;
			case ObjectType::Enemy:
				inRoom.AddRoomObject(mParsedEntites.at(std::stoi(dataToAdd)));
				break;
			case ObjectType::Entity:
				inRoom.AddRoomObject(mParsedEntites.at(std::stoi(dataToAdd)));
				break;
			case ObjectType::Weapon:
				inRoom.AddRoomObject(mParsedEntites.at(std::stoi(dataToAdd)));
				break;
			case ObjectType::Item:
				inRoom.AddRoomObject(mParsedEntites.at(std::stoi(dataToAdd)));
				break;
			case ObjectType::Room:
				inRoom.AddRoomObject(mParsedEntites.at(std::stoi(dataToAdd)));
				break;
			default:
				break;
			}
			StripCurrTag();
			currTag = FetchTag();
		}

		break;
	}

}

void Parser::CreateEnemy()
{
	Enemy newEnemy = Enemy();
	std::string nextTag = FetchTag();
	DataType dataType = DataType::Empty;
	StrToDataType(nextTag, dataType);
	StripCurrTag();

	while (dataType != DataType::Empty)
	{
		SetEnemyData(dataType, newEnemy);
		StripCurrTag();

		nextTag = FetchTag();
		StrToDataType(nextTag, dataType);
		StripCurrTag();
	}

	mParsedEntites.push_back(std::make_shared<Enemy>(newEnemy));
}

void Parser::SetEnemyData(DataType dataType, Enemy& inEnemy)
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

void Parser::CreateItem()
{
	Item newItem = Item();
	std::string nextTag = FetchTag();
	DataType dataType = DataType::Empty;
	StrToDataType(nextTag, dataType);
	StripCurrTag();

	while (dataType != DataType::Empty)
	{
		SetItemData(dataType, newItem);
		StripCurrTag();

		nextTag = FetchTag();
		StrToDataType(nextTag, dataType);
		StripCurrTag();
	}

	mParsedEntites.push_back(std::make_shared<Item>(newItem));
}

void Parser::SetItemData(DataType dataType, Item& inItem)
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

void Parser::CreateCharacter()
{
	Character newCharacter = Character();
	std::string nextTag = FetchTag();
	DataType dataType = DataType::Empty;
	StrToDataType(nextTag, dataType);
	StripCurrTag();

	while (dataType != DataType::Empty)
	{
		SetCharacterData(dataType, newCharacter);
		StripCurrTag();

		nextTag = FetchTag();
		StrToDataType(nextTag, dataType);
		StripCurrTag();
	}

	mParsedEntites.push_back(std::make_shared<Character>(newCharacter));
}

void Parser::SetCharacterData(DataType dataType, Character& inCharacter)
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

void Parser::CreateEntity()
{
	Entity newEntity = Entity();
	std::string nextTag = FetchTag();
	DataType dataType = DataType::Empty;
	StrToDataType(nextTag, dataType);
	StripCurrTag();

	while (dataType != DataType::Empty)
	{
		SetEntityData(dataType, newEntity);
		StripCurrTag();

		nextTag = FetchTag();
		StrToDataType(nextTag, dataType);
		StripCurrTag();
	}

	mParsedEntites.push_back(std::make_shared<Entity>(newEntity));
}

void Parser::SetEntityData(DataType dataType, Entity& inEntity)
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

void Parser::CreateWeapon()
{
	Weapon newWeapon = Weapon();
	std::string nextTag = FetchTag();
	DataType dataType = DataType::Empty;
	StrToDataType(nextTag, dataType);
	StripCurrTag();

	while (dataType != DataType::Empty)
	{
		SetWeaponData(dataType, newWeapon);
		StripCurrTag();

		nextTag = FetchTag();
		StrToDataType(nextTag, dataType);
		StripCurrTag();
	}

	mParsedEntites.push_back(std::make_shared<Weapon>(newWeapon));
}

void Parser::SetWeaponData(DataType dataType, Weapon& inWeapon)
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