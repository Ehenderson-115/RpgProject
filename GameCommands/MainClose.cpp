#include "MainClose.h"

MainClose::MainClose(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainClose::Execute()
{
	mGameData->State(Game::GameState::Closing);
}
