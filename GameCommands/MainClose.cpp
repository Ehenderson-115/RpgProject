#include "MainClose.h"

MainClose::MainClose(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainClose::Execute()
{
	mPlayerData->State(ClientData::GameState::Closing);
}
