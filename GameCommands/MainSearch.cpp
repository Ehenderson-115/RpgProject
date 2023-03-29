#include "MainSearch.h"
#include "Room.h"
#include "OutputManager.h"
#include "World.h"
#include "Player.h"


MainSearch::MainSearch(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainSearch::Execute()
{
	std::string searchResult = (mPlayerData->mRoom->CheckRoomContents());
	auto playersInRoom = mPlayerData->mWorld->GetOtherPlayers(mPlayerData->mPlayer);
	if (!playersInRoom.empty())
	{
		for (auto player : playersInRoom)
		{
			if (searchResult.empty())
			{
				searchResult += "\nYou see ";
			}
			else
			{
				searchResult += "\nYou also see ";
			}
			searchResult += player->Name();
			searchResult += " they could be either friend or foe.\n";
		}
	}
	if (searchResult.empty())
	{
		searchResult = "There is nothing of interest in this room\n";
	}
	mPlayerData->mOutputManager->AppendToOutput(searchResult);
}
