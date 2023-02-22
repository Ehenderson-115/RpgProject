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
	argument = GrabNextArg(mArgs);

	auto nextRoom = mGameData->mRoom->ConnectedRoom(argument);
	if (nextRoom != nullptr)
	{
		mGameData->mPlayer->Location(nextRoom);
		mGameData->mRoom = nextRoom;
		Game::UpdateHud(mGameData);
		FormattedPrint("You enter the room.");
	}
	else if (nextRoom == nullptr) 
	{
		FormattedPrint("The direction \"" + argument + "\" is invalid.");
	}
	else
	{
		FormattedPrint("There is nothing in that direction.");
	}
}
