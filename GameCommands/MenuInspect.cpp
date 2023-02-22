#include "MenuInspect.h"
#include "../GameObjects/HelperFunctions.h"
#include "../GameObjects/Player.h"

MenuInspect::MenuInspect(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuInspect::Execute()
{
	FormattedPrint(mGameData->mPlayer->CheckItem(mArgs));
}
