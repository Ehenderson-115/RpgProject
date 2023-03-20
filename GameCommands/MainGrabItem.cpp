#include "MainGrabItem.h"
#include "OutputManager.h"
#include "Room.h"
#include "Player.h"
#include "Item.h"

MainGrabItem::MainGrabItem(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainGrabItem::Execute()
{
	auto foundItem = mGameData->mRoom->GetItem(mArgs);
	if (foundItem != nullptr)
	{
		mGameData->mPlayer->AddItem(foundItem);
		mGameData->mOutputManager->AppendToOutput("You picked up the " + foundItem->Name());
	}
	else
	{
		mGameData->mOutputManager->AppendToOutput("There is no item with the name " + mArgs);
	}

}