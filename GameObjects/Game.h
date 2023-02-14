#ifndef GAME_H
#define GAME_H
#include <string>
#include <memory>
#include <vector>

class Room;
class Player;
class Character;
class Entity;

class Game
{
public:
	void StartGame();

private:
	enum class GameState {Error, Loading, Menu, Combat, Main};
	
	void GameLoop();
	
	std::string FormatCommand(std::string inStr);
	std::string GrabNextArg(std::string inStr);

	void ProcessUserCommand();
	void ProcessAdversaryCommand();
	
	//Main Commands
	void ExecuteMainCommand(const std::string& command);
	void MainMove();
	void MainLook();
	void MainOpen();
	void MainClose();
	void MainGrabItem();
	void MainSearch();
	void MainStartCombat();

	//Menu Commands
	void ExecuteMenuCommand(const std::string& command);
	void MenuListItems();
	void MenuClose();
	void MenuInspectItem();
	void MenuLook();
	void MenuEquip();

	//Combat Commands
	void ExecuteCombatCommand(const std::string& command, bool isPlayerAction);
	void CombatAttack(bool isPlayerAction);
	void CombatDefend(bool isPlayerAction);
	//Unused for now
	void CombatFlee(bool isPlayerAction);
	void EndCombat();

	void PrintHud();
	void UpdateHud();

	void UpdateState(GameState inState);
	

	void InvalidCommand(const std::string& command);

	bool runGame;
	int randOffset;
	GameState currState;
	std::string commandStr;
	std::vector<std::string>commands;

	std::shared_ptr<Player> currPlayer;
	std::shared_ptr<Room> currRoom;
	std::shared_ptr<Character> currAdversary;
	std::vector<std::shared_ptr<Entity>> mGameEntities;

};


#endif // !GAME_H
