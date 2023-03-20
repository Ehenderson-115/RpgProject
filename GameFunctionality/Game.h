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
	
	std::string ExecuteCommand(const std::string playerName, const std::string userCommand);

private:
	std::shared_ptr<Room> FindStartingRoom();

	std::string GetPlayerStateString(const std::shared_ptr<ClientData>& playerData);

	void DoCombatLogic(std::shared_ptr<ClientData>& playerData);

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
