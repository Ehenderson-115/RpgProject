#include "MenuEquip.h"
#include "../GameObjects/OutputManager.h"
#include "../GameObjects/Player.h"

MenuEquip::MenuEquip(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuEquip::Execute()
{
	std::string result = mGameData->mPlayer->EquipWeapon(mArgs);
	mGameData->mOutputManager->AddToOutput(result);
}
