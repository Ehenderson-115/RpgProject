#include "MainSearch.h"
#include "../GameObjects/Room.h"
#include "../GameObjects/OutputManager.h"


MainSearch::MainSearch(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainSearch::Execute()
{
	mGameData->mOutputManager->AddToOutput(mGameData->mRoom->CheckRoomContents());
}
