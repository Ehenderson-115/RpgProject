#include "MenuInspect.h"
#include "OutputManager.h"
#include "Player.h"

MenuInspect::MenuInspect(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuInspect::Execute()
{
	mGameData->mOutputManager->AppendToOutput(mGameData->mPlayer->CheckItem(mArgs));
}
