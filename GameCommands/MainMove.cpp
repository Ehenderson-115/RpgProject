#include "MainMove.h"
#include "OutputManager.h"
#include "HelperFunctions.h"
#include "Room.h"
#include "Player.h"
#include "World.h"
#include "Character.h"

MainMove::MainMove(std::shared_ptr<ClientData> inData, std::string inArgs)
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
		mGameData->mOutputManager->AppendToOutput("You enter the room.");
	}
	else if (nextRoom == nullptr) 
	{
		mGameData->mOutputManager->AppendToOutput("The direction \"" + argument + "\" is invalid.");
	}
	else
	{
		mGameData->mOutputManager->AppendToOutput("There is nothing in that direction.");
	}
}
