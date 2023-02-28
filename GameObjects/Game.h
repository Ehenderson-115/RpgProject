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
class World;
class OutputManager;
struct ActiveGameData;

class Game
{
public:
	enum class GameState { Error, Loading, Menu, Combat, CombatStart, Main, Closing};
	
	void StartGame();
private:

	std::shared_ptr<Room> FindStartingRoom();

	void GameLoop();
	
	std::string FormatCommand(std::string inStr);

	std::shared_ptr<Player> CreatePlayer();
	
	void DoCombatLogic();
	
	void ProcessAdversaryCommand();

	bool isCombatOver();


	void HandleCombatEnd();

	void UpdateGameData();

	void UpdateState(GameState inState);
	void HandleInvalidCommand(const std::string& commmand);

	std::shared_ptr<CommandParser> mCommandParser;
	std::shared_ptr<ActiveGameData> mActiveData;

	GameState mCurrState;

	std::string mCommandStr;

	std::shared_ptr<Player> mCurrPlayer;
	std::shared_ptr<Room> mCurrRoom;
	std::shared_ptr<Character> mCurrAdversary;
	std::shared_ptr<World> mWorld;

	std::shared_ptr<OutputManager> mOutputManager;

	std::vector<std::shared_ptr<Entity>> mGameEntities;


};


#endif // !GAME_H
