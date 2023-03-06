#include "MainMove.h"
#include "../GameObjects/OutputManager.h"
#include "../GameObjects/HelperFunctions.h"
#include "../GameObjects/Room.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/World.h"
#include "../GameObjects/Character.h"

MainMove::MainMove(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainMove::Execute()
{
	std::string argument;
	argument = GrabNextArg(mArgs);

	auto nextRoom = mGameData->mWorld->GetConnectedRoom(mGameData->mRoom, RoomConnection::TranslateDirection(argument));
	if (nextRoom != nullptr)
	{
		mGameData->mWorld->AddPlayerLocation(mGameData->mPlayer, nextRoom);
		mGameData->mRoom = nextRoom;
		mGameData->mOutputManager->AddToOutput("You enter the room.");
	}
	else if (nextRoom == nullptr) 
	{
		mGameData->mOutputManager->AddToOutput("The direction \"" + argument + "\" is invalid.");
	}
	else
	{
		mGameData->mOutputManager->AddToOutput("There is nothing in that direction.");
	}
}
