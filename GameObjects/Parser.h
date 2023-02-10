#ifndef PARSER_H
#define PARSER_H
#include <memory>
#include <vector>

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
	std::vector<std::shared_ptr<Entity>> InitGameDataFromFile(const std::string& fileToParse);

private:
	enum class ObjectType { Empty, Player, Character, Enemy, Entity, Weapon, Item, Room };
	enum class DataType { Empty, ID, Name, Race, Hitpoints, Descript, Damage, South, North, East, West, Contents };
	
	std::string dataSource;

	ObjectType ConsumeObjTag();
	DataType ConsumeDataTag();
	void ParseFileData();

	void LoadObject(const ObjectType& obj);

	void CreateCharacter();
	void CreateEntity();
	void CreateWeapon();
	void CreatePlayer();
	void CreateRoom();
	void CreateEnemy();
	void CreateItem();

	void SetData(const DataType& dataType, Player& inPlayer);
	void SetData(const DataType& dataType, Room& inRoom);
	void SetData(const DataType& dataType, Enemy& inEnemy);
	void SetData(const DataType& dataType, Item& inItem);
	void SetData(const DataType& dataType, Character& inCharacter);
	void SetData(const DataType& dataType, Entity& inEntity);
	void SetData(const DataType& dataType, Weapon& inWeapon);

	ObjectType TagToObjType(const std::string& tag);
	DataType TagToDataType(const std::string& tag);

	std::string FetchTag() const;
	void StripCurrTag();

	std::vector<std::shared_ptr<Entity>> mParsedEntites;
};


#endif