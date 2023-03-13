#include "Client.h"
#include "RpgGameConfig.h"
#include <string>
#include "asio.hpp"

int main(int argc, char* argv[])
{	
	Client myClient;
	myClient.InitServerConnection();

  return 0;
}
