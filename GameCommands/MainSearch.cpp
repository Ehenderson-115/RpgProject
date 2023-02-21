#include "MainSearch.h"
#include "../GameObjects/Room.h"
#include "../GameObjects/HelperFunctions.h"


MainSearch::MainSearch(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainSearch::Execute()
{
	FormattedPrint(mGameData->mRoom->CheckRoomContents());
}
