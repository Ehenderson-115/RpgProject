#include "MenuInspect.h"
#include "../GameObjects/OutputManager.h"
#include "../GameObjects/Player.h"

MenuInspect::MenuInspect(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuInspect::Execute()
{
	mGameData->mOutputManager->AddToOutput(mGameData->mPlayer->CheckItem(mArgs));
}
