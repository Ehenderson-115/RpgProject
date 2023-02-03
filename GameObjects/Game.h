#ifndef GAME_H
#define GAME_H
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
class Game

{
public:
	void StartGame();

private:
	enum class ObjectType {Empty, Player, Character, Enemy, Entity, Weapon, Item, Room};
	enum class DataType {Empty, ID, Name, Race, Hitpoints, Descript, Damage, South, North, East, West};

	void ConsumeObjTag(ObjectType &obj, std::string &dataSource);
	void ConsumeDataTag(DataType &dataT, std::string &dataSource);

	void ParseConfigFile();
	void ParseFileData(std::string &dataSource);

	void LoadObject(ObjectType obj, std::string &dataSource);

	void CreateCharacter(std::string &dataSource);
	void CreateEntity(std::string &dataSource);
	void CreateWeapon(std::string &dataSource);
	void CreatePlayer(std::string &dataSource);
	void CreateRoom(std::string &dataSource);
	void CreateEnemy(std::string &dataSource);
	void CreateItem(std::string& dataSource);

	void SetPlayerData(DataType dataType, std::string& dataSource, Player& inPlayer);
	void SetRoomData(DataType dataType, std::string& dataSource, Room& inRoom);
	void SetEnemyData(DataType dataType, std::string& dataSource, Enemy& inEnemy);
	void SetItemData(DataType dataType, std::string& dataSource, Item& inItem);
	void SetCharacterData(DataType dataType, std::string& dataSource, Character& inCharacter);
	void SetEntityData(DataType dataType, std::string& dataSource, Entity& inEntity);
	void SetWeaponData(DataType dataType, std::string& dataSource, Weapon& inWeapon);

	void UpdateObjType(std::string tag, ObjectType &inObj);
	void UpdateDataType(std::string tag, DataType &inDataType);

	std::string FetchTag(std::string &dataSource);
	void StripCurrTag(std::string& dataSource);

	std::vector<std::shared_ptr<Entity>> mGameEntities;






};


#endif // !GAME_H
