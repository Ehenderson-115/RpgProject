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
	
	std::string ProcessUserCommand(const std::string playerName, const std::string userCommand);
	bool CheckPlayerAttacked(std::shared_ptr<ClientData>& playerData);

private:
	std::shared_ptr<Room> FindStartingRoom();

	std::shared_ptr<ClientData> FindAttackingPlayerData(const std::shared_ptr<Player>& inPlayer);
	
	void InitPvp(std::shared_ptr<ClientData>& playerData);

	std::string GetPlayerStateString(const std::shared_ptr<ClientData>& playerData);

	std::string GetCombatResult (std::shared_ptr<ClientData>& playerData);

	void DoPvpCombat(std::shared_ptr<ClientData>& playerData);

	void DoNpcCombat(std::shared_ptr<ClientData>& playerData);

	void ProcessAdversaryCommand(std::shared_ptr<ClientData>& playerData);

	bool IsCombatOver(std::shared_ptr<ClientData>& playerData);

	bool IsNewPlayer(const std::string& playerName);

	std::shared_ptr<ClientData> GetPlayerData(const std::string& playerName);

	void HandleCombatEnd(std::shared_ptr<ClientData>& playerData);

	std::shared_ptr<CommandParser> mCommandParser;
	std::shared_ptr<Room> mStartingRoom;
	std::string mCommandStr;
	std::mutex mMutex;

	std::vector<std::shared_ptr<Entity>> mGameEntities;
	std::vector<std::shared_ptr<ClientData>> mActivePlayerData;
	

};


#endif // !GAME_H
