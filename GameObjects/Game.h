#ifndef GAME_H
#define GAME_H
#include <string>
#include <memory>
#include <vector>
#include "../ThirdPartyLibraries/asio-1.24.0/include/asio.hpp"


class Room;
class Player;
class Entity;
class CommandParser;
struct ClientData;

class Game
{
public:
	Game();
	void TestConnection();
	void InitServer();
private:
	//Networking Functions
	unsigned short GetPortFromUser();
	void AcceptNewClientConnections();
	static void Session(asio::ip::tcp::socket socket);

	std::shared_ptr<Room> FindStartingRoom();

	void GameLoop();
	
	std::string FormatCommand(std::string inStr);

	std::shared_ptr<Player> CreatePlayer();
	
	void DoCombatLogic();
	
	void ProcessAdversaryCommand();

	bool isCombatOver();

	void HandleCombatEnd();

	void HandleInvalidCommand(const std::string& commmand);

	std::shared_ptr<ClientData> mActiveData;
	std::shared_ptr<Room> mStartingRoom;
	std::vector<std::shared_ptr<Entity>> mGameEntities;
	std::mutex mMutex;
	unsigned short mPort;
	asio::io_context mIo;
	asio::ip::tcp::acceptor mAcceptor;
	std::string mCommandStr;
	std::shared_ptr<CommandParser> mCommandParser;
	

};


#endif // !GAME_H
