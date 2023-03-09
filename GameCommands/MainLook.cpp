#include "MainLook.h"
#include "../GameObjects/OutputManager.h"
#include "../GameObjects/Room.h"

MainLook::MainLook(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainLook::Execute()
{
	mGameData->mOutputManager->AddToOutput(mGameData->mRoom->Descript());
}

