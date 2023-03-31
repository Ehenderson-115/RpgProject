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

	auto nextRoom = mPlayerData->mWorld->GetConnectedRoom(mPlayerData->mRoom, RoomConnection::TranslateDirection(argument));
	if (nextRoom != nullptr)
	{
		mPlayerData->mWorld->AddPlayerLocation(mPlayerData->mPlayer, nextRoom);
		mPlayerData->mRoom = nextRoom;
		mPlayerData->mOutputManager->AppendToOutput("You enter the room.");
	}
	else if (nextRoom == nullptr) 
	{
		mPlayerData->mOutputManager->AppendToOutput("The direction \"" + argument + "\" is invalid.");
	}
	else
	{
		mPlayerData->mOutputManager->AppendToOutput("There is nothing in that direction.");
	}
}
