#include "Client.h"
#include <string>
#include "asio.hpp"

int main(int argc, char* argv[])
{	
	asio::io_context io;
	Client myClient(io);
	myClient.ConnectToServer();

  return 0;
}
