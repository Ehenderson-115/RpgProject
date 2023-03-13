#include "MainSearch.h"
#include "Room.h"
#include "OutputManager.h"


MainSearch::MainSearch(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainSearch::Execute()
{
	mGameData->mOutputManager->AddToOutput(mGameData->mRoom->CheckRoomContents());
}
