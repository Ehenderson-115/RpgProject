#include "Parser.h"
#include "Player.h"
#include "Room.h"
#include "Entity.h"
#include "Character.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Item.h"
#include "HelperFunctions.h"

std::string Parser::FetchTag() const
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

Parser::ObjectType Parser::ConsumeObjTag()
{
	std::string tag = FetchTag();
	StripCurrTag();
	return TagToObjType(tag);
}

Parser::DataType Parser::ConsumeDataTag()
{
	std::string tag = FetchTag();
	StripCurrTag();
	return TagToDataType(tag);
}

std::vector<std::shared_ptr<Entity>> Parser::InitGameDataFromFile(const std::string& fileToParse)
{
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

	StripString(fileStr, "\t");
	dataSource = fileStr;
	ParseFileData();
	return mParsedEntites;
}

void Parser::ParseFileData()
{
	ObjectType obj = ObjectType::Empty;
	int startOfTags = dataSource.find_first_of(">");
	int endOfTags = dataSource.find_last_of(">");

	while (startOfTags != endOfTags)
	{

		obj = ConsumeObjTag();
		LoadObject(obj);

		obj = ObjectType::Empty;

		startOfTags = dataSource.find_first_of(">");
		endOfTags = dataSource.find_last_of(">");
	}
}

void Parser::LoadObject(const ObjectType& obj)
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

Parser::ObjectType Parser::TagToObjType(const std::string& tag)
{
	if (tag == "<player>")
	{
		return ObjectType::Player;
	}
	else if (tag == "<character>")
	{
		return ObjectType::Character;
	}
	else if (tag == "<entity>")
	{
		return ObjectType::Entity;
	}
	else if (tag == "<weapon>")
	{
		return ObjectType::Weapon;
	}
	else if (tag == "<enemy>")
	{
		return ObjectType::Enemy;
	}
	else if (tag == "<item>")
	{
		return ObjectType::Item;
	}
	else if (tag == "<room>")
	{
		return ObjectType::Room;
	}
	else
	{
		return ObjectType::Empty;
	}
}

Parser::DataType Parser::TagToDataType(const std::string& tag)
{
	if (tag == "<id>")
	{
		return DataType::ID;
	}
	else if (tag == "<name>")
	{
		return DataType::Name;
	}
	else if (tag == "<race>")
	{
		return DataType::Race;
	}
	else if (tag == "<hitpoints>")
	{
		return DataType::Hitpoints;
	}
	else if (tag == "<descript>")
	{
		return DataType::Descript;
	}
	else if (tag == "<damage>")
	{
		return DataType::Damage;
	}
	else if (tag == "<north>")
	{
		return DataType::North;
	}
	else if (tag == "<south>")
	{
		return DataType::South;
	}
	else if (tag == "<east>")
	{
		return DataType::East;
	}
	else if (tag == "<west>")
	{
		return DataType::West;
	}
	else if (tag == "<contents>")
	{
		return DataType::Contents;
	}
	else
	{
		return DataType::Empty;
	}
}

void Parser::CreatePlayer()
{
	Player newPlayer = Player();
	std::string nextTag = FetchTag();
	DataType dataType = ConsumeDataTag();

	while (dataType != DataType::Empty)
	{
		SetData(dataType, newPlayer);
		StripCurrTag();
		dataType = ConsumeDataTag();
	}

	mParsedEntites.push_back(std::make_shared<Player>(newPlayer));
}

void Parser::SetData(const DataType& dataType, Player& inPlayer)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inPlayer.Id(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inPlayer.Name(dataToAdd);
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
	DataType dataType = ConsumeDataTag();

	while (dataType != DataType::Empty)
	{
		SetData(dataType, newRoom);
		StripCurrTag();
		dataType = ConsumeDataTag();
	}

	mParsedEntites.push_back(std::make_shared<Room>(newRoom));
}

void Parser::SetData(const DataType& dataType, Room& inRoom)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	DataType contentType = DataType::Empty;
	ObjectType contentObjType = ObjectType::Empty;
	std::string currTag = "";
	switch (dataType)
	{
	case DataType::ID:
		inRoom.Id(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inRoom.Name(dataToAdd);
		break;
	case DataType::Descript:
		inRoom.Descript(dataToAdd);
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
	case DataType::Contents:
		currTag = FetchTag();
		while (currTag != "</contents>")
		{
			contentObjType = ConsumeObjTag();
			dataToAdd = dataSource.substr(0, dataSource.find("<"));
			std::shared_ptr<Player> roomPlayer = nullptr;
			switch (contentObjType)
			{
			case ObjectType::Player:
				roomPlayer = std::static_pointer_cast<Player>(mParsedEntites.at(std::stoi(dataToAdd)));
				roomPlayer->SetCurrRoomId(inRoom.Id());
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
	DataType dataType = ConsumeDataTag();

	while (dataType != DataType::Empty)
	{
		SetData(dataType, newEnemy);
		StripCurrTag();
		dataType = ConsumeDataTag();

	}

	mParsedEntites.push_back(std::make_shared<Enemy>(newEnemy));
}

void Parser::SetData(const DataType& dataType, Enemy& inEnemy)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inEnemy.Id(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inEnemy.Name(dataToAdd);
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
	DataType dataType = ConsumeDataTag();

	while (dataType != DataType::Empty)
	{
		SetData(dataType, newItem);
		StripCurrTag();
		dataType = ConsumeDataTag();
	}

	mParsedEntites.push_back(std::make_shared<Item>(newItem));
}

void Parser::SetData(const DataType& dataType, Item& inItem)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inItem.Id(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inItem.Name(dataToAdd);
		break;
	case DataType::Descript:
		inItem.Descript(dataToAdd);
		break;
	}
}

void Parser::CreateCharacter()
{
	Character newCharacter = Character();
	std::string nextTag = FetchTag();
	DataType dataType = ConsumeDataTag();

	while (dataType != DataType::Empty)
	{
		SetData(dataType, newCharacter);
		StripCurrTag();
		dataType = ConsumeDataTag();
	}

	mParsedEntites.push_back(std::make_shared<Character>(newCharacter));
}

void Parser::SetData(const DataType& dataType, Character& inCharacter)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inCharacter.Id(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inCharacter.Name(dataToAdd);
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
	DataType dataType = ConsumeDataTag();

	while (dataType != DataType::Empty)
	{
		SetData(dataType, newEntity);
		StripCurrTag();
		dataType = ConsumeDataTag();
	}

	mParsedEntites.push_back(std::make_shared<Entity>(newEntity));
}

void Parser::SetData(const DataType& dataType, Entity& inEntity)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inEntity.Id(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inEntity.Name(dataToAdd);
		break;
	case DataType::Descript:
		inEntity.Descript(dataToAdd);
		break;
	}
}

void Parser::CreateWeapon()
{
	Weapon newWeapon = Weapon();
	std::string nextTag = FetchTag();
	DataType dataType = ConsumeDataTag();

	while (dataType != DataType::Empty)
	{
		SetData(dataType, newWeapon);
		StripCurrTag();
		dataType = ConsumeDataTag();
	}

	mParsedEntites.push_back(std::make_shared<Weapon>(newWeapon));
}

void Parser::SetData(const DataType& dataType, Weapon& inWeapon)
{
	std::string dataToAdd = dataSource.substr(0, dataSource.find("<"));
	switch (dataType)
	{
	case DataType::ID:
		inWeapon.Id(std::stoi(dataToAdd));
		break;
	case DataType::Name:
		inWeapon.Name(dataToAdd);
		break;
	case DataType::Descript:
		inWeapon.Descript(dataToAdd);
		break;
	case DataType::Damage:
		inWeapon.SetDamage(std::stoi(dataToAdd));
		break;
	}
}