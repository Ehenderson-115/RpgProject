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
	//std::lock_guard<std::mutex> lGuard(mGameData->mMutex);
	auto foundItem = mPlayerData->mRoom->GetItem(mArgs);
	if (foundItem != nullptr)
	{
		mPlayerData->mPlayer->AddItem(foundItem);
		mPlayerData->mOutputManager->AppendToOutput("You picked up the " + foundItem->Name());
	}
	else
	{
		mPlayerData->mOutputManager->AppendToOutput("There is no item with the name " + mArgs);
	}

}