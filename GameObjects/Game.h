#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include <vector>
#include <typeinfo>


class Player;
class Character;
class Enemy;
class Entity;
class Item;
class Room;
class Weapon;
class Parser;

class Game
{
public:
	void StartGame();

private:
	//Unused for now
	enum class Command {Unknown, Move, Pickup, Look, Search, Attack};

	enum class GameState {Error, Loading, Menu, Combat, Main};
	
	void GameLoop();
	void ParseCommand(std::string& inCommandStr);
	void ExecuteCommand(std::string& inCommandStr, std::vector<std::string>& inCommandVect);
	
	bool runGame;
	GameState currState;

	std::shared_ptr<Player> currPlayer;
	std::shared_ptr<Room> currRoom;
	std::vector<std::shared_ptr<Entity>> mGameEntities;

};


#endif // !GAME_H
