#include "asio.hpp"
#include <string>
#include <memory>
class Game;

//Helper methods
std::string ReadStringFromSocket(const asio::ip::tcp::socket& inSocket);
std::string WriteStringToSocket(const asio::ip::tcp::socket& inSocket);
std::string GetPortFromConfigFile(std::string filePath);
std::string GetHostnameFromConfigFile(std::string filePath);
unsigned short StringToValidPort(std::string strPort);

//Server Methods
void AcceptClientConnections(unsigned short port, std::shared_ptr<Game>& gameInstance);
void Session(asio::ip::tcp::socket socket, std::shared_ptr<Game>& gameInstance);

//Client Methods
