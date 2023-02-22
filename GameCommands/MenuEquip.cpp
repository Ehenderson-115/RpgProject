#include "MenuEquip.h"
#include "../GameObjects/HelperFunctions.h"
#include "../GameObjects/Player.h"

MenuEquip::MenuEquip(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuEquip::Execute()
{
	std::string result = mGameData->mPlayer->EquipWeapon(mArgs);
	Game::UpdateHud(mGameData);
	FormattedPrint(result);
}
