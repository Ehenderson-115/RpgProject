#include "MainOpen.h"
#include "../GameObjects/OutputManager.h"
#include "../GameObjects/HelperFunctions.h"

MainOpen::MainOpen(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainOpen::Execute()
{
	std::string argument = GrabNextArg(mArgs);
	if (argument == "inventory" || argument == "i")
	{
		mGameData->mState = Game::GameState::Menu;
	}
	else
	{
		mGameData->mOutputManager->AddToOutput("Invalid target " + argument);
	}
}
