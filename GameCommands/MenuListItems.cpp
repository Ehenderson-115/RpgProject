#include "MenuListItems.h"
#include "Player.h"
#include "OutputManager.h"

MenuListItems::MenuListItems(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuListItems::Execute()
{
	mPlayerData->mOutputManager->AppendToOutput(mPlayerData->mPlayer->CheckInventory());
}
