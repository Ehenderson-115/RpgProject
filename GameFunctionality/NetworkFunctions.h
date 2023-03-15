#include "asio.hpp"
#include <string>

std::string ReadStringFromSocket(const asio::ip::tcp& inSocket);
std::string WriteStringToSocket(const asio::ip::tcp& inSocket);