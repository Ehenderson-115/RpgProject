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
	enum class DataType {Empty, ID, Name, Race, Hitpoints, Descript, Damage};

	void ConsumeTypeTag(ObjectType &obj, std::string &dataSource);
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
	void CreateItem(std::string &dataSource);
	void TagToObjType(std::string tag, ObjectType &objectType);
	void FindObjEndTag(ObjectType obj, std::string dataSource);








};


#endif // !GAME_H
