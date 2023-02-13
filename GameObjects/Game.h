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
	std::string GrabNextArg(std::string inStr);

	void ProcessUserCommands();
	
	void ExecuteMainCommand(const std::string& command);
	void Main_Move();
	void Main_Look();
	void Main_Open();
	void Main_Close();
	void Main_GrabItem();
	void Main_Search();
	void Main_StartCombat();

	void ExecuteMenuCommand(const std::string& command);
	void Menu_ListItems();
	void Menu_Close();
	void Menu_InspectItem();
	void Menu_Look();
	void Menu_Equip();

	void PrintHud();
	void UpdateHud();
	


	void InvalidCommand(const std::string& command);

	bool runGame;
	GameState currState;
	std::string commandStr;
	std::vector<std::string>commands;

	std::shared_ptr<Player> currPlayer;
	std::shared_ptr<Room> currRoom;
	std::vector<std::shared_ptr<Entity>> mGameEntities;

};


#endif // !GAME_H
