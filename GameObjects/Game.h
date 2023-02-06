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
class Parser;

class Game
{
public:
	void StartGame();

private:
	std::vector<std::shared_ptr<Entity>> mGameEntities;






};


#endif // !GAME_H
