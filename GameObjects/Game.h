#ifndef GAME_H
#define GAME_H
#include <string>
#include <memory>
#include <vector>

class Room;
class Player;
class Entity;

class Game
{
public:
	void StartGame();

private:
	//Unused for now
	enum class Command {Unknown, Move, Pickup, Look, Search, Attack};

	enum class GameState {Error, Loading, Menu, Combat, Main};
	
	void GameLoop();
	std::string FormatCommand(std::string inStr);
	void ExecuteCommand(std::string& inCommandStr, std::vector<std::string>& inCommandVect);
	
	bool runGame;
	GameState currState;

	std::shared_ptr<Player> currPlayer;
	std::shared_ptr<Room> currRoom;
	std::vector<std::shared_ptr<Entity>> mGameEntities;

};


#endif // !GAME_H
