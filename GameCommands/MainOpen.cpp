#include "MainOpen.h"
#include "OutputManager.h"
#include "HelperFunctions.h"

MainOpen::MainOpen(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainOpen::Execute()
{
	std::string argument = GrabNextArg(mArgs);
	if (argument == "inventory" || argument == "i")
	{
		mGameData->State(ClientData::GameState::Menu);
	}
	else
	{
		mGameData->mOutputManager->AddToOutput("Invalid target " + argument);
	}
}
