#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>



class Character;
class Enemy;
class Entity;
class Item;
class Player;
class Room;
class Weapon;

class Parser
{

public:
	std::vector<std::shared_ptr<Entity>> ParseConfigFile(const std::string& fileToParse);

private:
	enum class ObjectType { Empty, Player, Character, Enemy, Entity, Weapon, Item, Room };
	enum class DataType { Empty, ID, Name, Race, Hitpoints, Descript, Damage, South, North, East, West, Contents };
	std::string dataSource;

	void ConsumeObjTag(ObjectType& obj);
	void ConsumeDataTag(DataType& dataT);
	void ParseFileData();

	void LoadObject(ObjectType obj);

	void CreateCharacter();
	void CreateEntity();
	void CreateWeapon();
	void CreatePlayer();
	void CreateRoom();
	void CreateEnemy();
	void CreateItem();

	void SetPlayerData(DataType dataType, Player& inPlayer);
	void SetRoomData(DataType dataType, Room& inRoom);
	void SetEnemyData(DataType dataType, Enemy& inEnemy);
	void SetItemData(DataType dataType, Item& inItem);
	void SetCharacterData(DataType dataType, Character& inCharacter);
	void SetEntityData(DataType dataType, Entity& inEntity);
	void SetWeaponData(DataType dataType, Weapon& inWeapon);

	void StrToObjType(std::string tag, ObjectType& inObj);
	void StrToDataType(std::string tag, DataType& inDataType);

	std::string FetchTag();
	void StripCurrTag();

	std::vector<std::shared_ptr<Entity>> mParsedEntites;
};


#endif