#include "MenuListItems.h"
#include "Player.h"
#include "OutputManager.h"

MenuListItems::MenuListItems(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuListItems::Execute()
{
	mGameData->mOutputManager->AddToOutput(mGameData->mPlayer->CheckInventory());
}
