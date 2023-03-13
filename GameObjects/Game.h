#ifndef GAME_H
#define GAME_H
#include <string>
#include <memory>
#include <vector>
#include "asio.hpp"


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
	void AcceptNewClientConnections();
	static void Session(asio::ip::tcp::socket socket, std::shared_ptr<Game> gamePtr);
	static std::string GetStringFromClient(const asio::ip::tcp::socket& inSocket);
	static void WriteStringToClient(const asio::ip::tcp::socket& inSocket, std::string);

	//Threading Functions
	std::shared_ptr<Room> FindStartingRoom();

	void GameLoop();
	
	std::string FormatCommand(std::string inStr);

	std::shared_ptr<Player> CreatePlayer(const asio::ip::tcp::socket& inSocket);
	
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
