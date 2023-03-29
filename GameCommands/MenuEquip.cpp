#include "MenuEquip.h"
#include "OutputManager.h"
#include "Player.h"

MenuEquip::MenuEquip(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuEquip::Execute()
{
	std::string result = mPlayerData->mPlayer->EquipWeapon(mArgs);
	mPlayerData->mOutputManager->AppendToOutput(result);
}
