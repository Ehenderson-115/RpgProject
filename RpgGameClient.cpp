#include "Client.h"
#include <string>
#include "asio.hpp"

int main(int argc, char* argv[])
{	
	Client myClient;
	myClient.InitServerConnection();

  return 0;
}
