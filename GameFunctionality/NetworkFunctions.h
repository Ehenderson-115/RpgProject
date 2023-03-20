#include "asio.hpp"
#include <string>
#include <memory>
class Game;

//Helper methods
std::string ReadStringFromSocket(asio::ip::tcp::socket& inSocket);
void WriteStringToSocket(asio::ip::tcp::socket& inSocket, std::string inStr);
std::string GetPortFromConfigFile(const std::string& filePath);
std::string GetHostnameFromConfigFile(const std::string& filePath);
unsigned short StringToValidPort(std::string strPort);
std::string FormatCommand(std::string inStr);

//Server Methods
void AcceptClientConnections(unsigned short port, std::shared_ptr<Game>& gameInstance);
void Session(asio::ip::tcp::socket socket, std::shared_ptr<Game>& gameInstance);
std::string AddClientToGame(asio::ip::tcp::socket& inSocket, std::shared_ptr<Game>& gameInstance);


//Client Methods
void InitServerConnection();
void DoClientLogic(asio::ip::tcp::socket& socket);
