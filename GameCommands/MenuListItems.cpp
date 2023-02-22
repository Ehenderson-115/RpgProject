#include "MenuListItems.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/HelperFunctions.h"

MenuListItems::MenuListItems(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuListItems::Execute()
{
	FormattedPrint(mGameData->mPlayer->CheckInventory());
}
