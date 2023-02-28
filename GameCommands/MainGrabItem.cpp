#include "MainGrabItem.h"
#include "../GameObjects/OutputManager.h"
#include "../GameObjects/Room.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Item.h"

MainGrabItem::MainGrabItem(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainGrabItem::Execute()
{
	auto foundItem = mGameData->mRoom->GetItem(mArgs);
	if (foundItem != nullptr)
	{
		mGameData->mPlayer->AddItem(foundItem);
		mGameData->mOutputManager->AddToOutput("You picked up the " + foundItem->Name());
	}
	else
	{
		mGameData->mOutputManager->AddToOutput("There is no item with the name " + mArgs);
	}

}