#include "MainLook.h"
#include "OutputManager.h"
#include "Room.h"

MainLook::MainLook(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainLook::Execute()
{
	mPlayerData->mOutputManager->AppendToOutput(mPlayerData->mRoom->Descript());
}

