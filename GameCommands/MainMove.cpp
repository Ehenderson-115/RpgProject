#include "MainMove.h"
#include "../GameObjects/HelperFunctions.h"
#include "../GameObjects/Room.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Character.h"

MainMove::MainMove(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainMove::Execute()
{
	std::string argument;
	argument = mGameData->mGame->GrabNextArg(mArgs);

	auto nextRoom = mGameData->mRoom->ConnectedRoom(argument);
	if (nextRoom != nullptr)
	{
		mGameData->mPlayer->Location(nextRoom);
		mGameData->mRoom = nextRoom;
		mGameData->mGame->UpdateHud();
		FormattedPrint("you enter the room.");
	}
	else if (nextRoom == nullptr) 
	{
		FormattedPrint("the direction \"" + argument + "\" is invalid.");
	}
	else
	{
		FormattedPrint("there is nothing in that direction.");
	}
}
