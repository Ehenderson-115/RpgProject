#ifndef GAME_H
#define GAME_H
#include <string>
#include <memory>
#include <vector>

class Room;
class Player;
class Entity;
class CommandParser;
struct ActiveGameData;

class Game
{
public:
	enum class GameState { Error, Menu, Combat, CombatStart, CombatEndMain, CombatEndClose, Main, Closing};
	
	void TestConnection();
	void InitServer();
private:
	//Networking Functions
	unsigned short GetPortFromUser();
	void InitNewClientConnection();
	void StartNewSession();
	void Session();

	std::shared_ptr<Room> FindStartingRoom();

	void GameLoop();
	
	std::string FormatCommand(std::string inStr);

	std::shared_ptr<Player> CreatePlayer();
	
	void DoCombatLogic();
	
	void ProcessAdversaryCommand();

	bool isCombatOver();

	void HandleCombatEnd();

	void HandleInvalidCommand(const std::string& commmand);

	std::shared_ptr<CommandParser> mCommandParser;
	std::shared_ptr<ActiveGameData> mActiveData;
	std::string mCommandStr;
	std::vector<std::shared_ptr<Entity>> mGameEntities;

	//asio::io_context mIo;
	//asio::ip::tcp::acceptor mAcceptor;
};


#endif // !GAME_H
