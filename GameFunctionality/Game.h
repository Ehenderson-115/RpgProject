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
class GameCommand;

class Game
{
public:

	void InitGame();
	bool AddNewPlayer(const std::string& playerName);
	
	std::string ProcessUserCommand(const std::string playerName, const std::string userCommand);
	void RemovePlayerFromWorld(const std::string playerName);
	

private:
	std::shared_ptr<Room> FindStartingRoom();

	std::shared_ptr<ClientData> FindAttackingPlayerData(const std::shared_ptr<Player>& inPlayer);
	
	void InitPvp(std::shared_ptr<ClientData>& playerData);

	std::string GetPlayerStateString(const std::shared_ptr<ClientData>& playerData);

	std::string GetCombatResult(std::shared_ptr<ClientData>& playerData, std::shared_ptr<GameCommand>& command);

	std::string HandlePvpEdgeCases(std::shared_ptr<ClientData>& playerData, const std::string& userCommand);

	bool PlayerAttacked(std::shared_ptr<ClientData>& playerData);

	void DoPvpCombat(std::shared_ptr<ClientData>& playerData, std::shared_ptr<GameCommand>& command);

	void DoNpcCombat(std::shared_ptr<ClientData>& playerData, std::shared_ptr<GameCommand>& command);

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
