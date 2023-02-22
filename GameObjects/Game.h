#ifndef GAME_H
#define GAME_H
#include <string>
#include <memory>
#include <vector>

class Room;
class Player;
class Character;
class Entity;
class CommandParser;
struct ActiveGameData;

class Game
{
public:
	enum class GameState { Error, Loading, Menu, Combat, CombatStart, Main, Closing};
	
	void StartGame();
	static void UpdateHud(const std::shared_ptr<ActiveGameData>& inData, const std::string& reprintStr = "");
	static void PrintHud(const std::shared_ptr<ActiveGameData>& inData);
private:
	
	void GameLoop();
	
	std::string FormatCommand(std::string inStr);

	void InitEntityPointers();

	void ProcessAdversaryCommand();
	
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
	void UpdateHud(const std::string& reprintStr="");

	void UpdateGameData();

	void UpdateState(GameState inState);
	void PrintInvalidCommand(const std::string& commmand);

	int randOffset;

	std::shared_ptr<CommandParser> commandParser;
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
