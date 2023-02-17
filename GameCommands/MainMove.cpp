#include "MainMove.h"
#include "../GameObjects/HelperFunctions.h"
#include "../GameObjects/Room.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Character.h"

void MainMove::Execute()
{
	std::string argument;
	argument = Game::GrabNextArg(mArgs);

	auto nextRoom = mGameData->mRoom->ConnectedRoom(argument);
	if (nextRoom != nullptr)
	{
		mGameData->mPlayer->Location(nextRoom);
		mGameData->mRoom = nextRoom;
		Game::UpdateHud();
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
