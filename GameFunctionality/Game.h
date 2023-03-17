#ifndef GAME_H
#define GAME_H
#include <string>
#include <memory>
#include <vector>
#include <mutex>


class Room;
class Player;
class Entity;
class CommandParser;
struct ClientData;

class Game
{
public:

	void InitGame();
	bool AddNewPlayer(const std::string& playerName);
	std::string GetPlayerStateString(const std::string& playerName);
private:
	std::shared_ptr<Room> FindStartingRoom();

	void GameLoop();

	std::string FormatCommand(std::string inStr);

	void DoCombatLogic();

	void ProcessAdversaryCommand();

	bool IsCombatOver();

	bool IsNewPlayer(const std::string& playerName);

	void HandleCombatEnd();

	void HandleInvalidCommand(const std::string& commmand);

	std::shared_ptr<CommandParser> mCommandParser;
	std::shared_ptr<ClientData> mCurrPlayerData;
	std::shared_ptr<Room> mStartingRoom;
	std::string mCommandStr;
	std::mutex mMutex;

	std::vector<std::shared_ptr<Entity>> mGameEntities;
	std::vector<std::shared_ptr<ClientData>> mActivePlayerData;
	

};


#endif // !GAME_H
