#ifndef GAME_H
#define GAME_H
#include <string>
#include <memory>
#include <vector>

class Room;
class Player;
class Character;
class Entity;
class CommandProcessor;
struct ActiveGameData;

class Game
{
public:
	enum class GameState { Error, Loading, Menu, Combat, Main };
	void StartGame();
	std::string GrabNextArg(std::string inStr);
	void UpdateHud(std::string reprintStr);
private:
	
	void GameLoop();
	
	std::string FormatCommand(std::string inStr);

	void InitEntityPointers();

	void ProcessUserCommand();
	void ProcessAdversaryCommand();
	
	//Main Commands
	void ExecuteMainCommand(const std::string& command);
	void MainMove();
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
	void ExecuteCombatCommand(const std::string& command);
	void CombatAttackPlayer();
	void CombatAttackAdversary();
	void CombatDefendAdversary();
	void CombatDefendPlayer();
	//Unused for now
	void CombatFleePlayer();
	void EndCombat();

	void PrintHud();
	

	void UpdateState(GameState inState);
	

	void InvalidCommand(const std::string& command);

	bool runGame;
	bool firstTurn;
	int randOffset;

	std::shared_ptr<CommandProcessor> commandProcessor;
	std::shared_ptr<ActiveGameData> activeData;

	std::string prevTurnResult;
	GameState currState;

	std::string commandInputStr;
	std::vector<std::string>commands;

	std::shared_ptr<Player> currPlayer;
	std::shared_ptr<Room> currRoom;
	std::shared_ptr<Character> currAdversary;

	std::vector<std::shared_ptr<Entity>> mGameEntities;

};


#endif // !GAME_H
