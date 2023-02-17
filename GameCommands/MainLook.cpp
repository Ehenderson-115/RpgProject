#include "MainLook.h"
#include "../GameObjects/HelperFunctions.h"
#include "../GameObjects/Room.h"

MainLook::MainLook(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainLook::Execute()
{
	FormattedPrint(mGameData->mRoom->Descript());
}

