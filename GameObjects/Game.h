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
	void ParseConfigFile();
	void ParseTag(std::string &input);
	void CreatePlayer();
	void CreateRoom();
	void CreateEnemy();
	void CreateItem();








};


#endif // !GAME_H
