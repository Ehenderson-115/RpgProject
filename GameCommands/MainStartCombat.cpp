#include "MainStartCombat.h"
#include "HelperFunctions.h"
#include "OutputManager.h"
#include "Room.h"
#include "World.h"
#include "Player.h"

MainStartCombat::MainStartCombat(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainStartCombat::Execute()
{
	std::lock_guard<std::mutex> lock(mGameData->mMutex);
	auto adversary = mGameData->mRoom->GetCharacter(mArgs);
	if (adversary == nullptr)
	{
		SafelyAddPlayerAdv();
		if (mGameData->mAdversary == nullptr)
		{
			mGameData->mOutputManager->AppendToOutput("The is no \"" + mArgs + "\" to fight.");
		}
	}
	else
	{
		if (adversary->InCombat())
		{
			mGameData->mOutputManager->AppendToOutput("That target is already in combat with someone else.");
		}
		else
		{
			mGameData->mPlayer->InCombat(true);
			adversary->InCombat(true);
			mGameData->State(ClientData::GameState::CombatStart);
		}
	}
}

void MainStartCombat::SafelyAddPlayerAdv()
{
	for (auto player : mGameData->mWorld->GetOtherPlayers(mGameData->mPlayer))
	{
		if (StrToLower(mArgs) == StrToLower(player->Name()))
		{
			if (!player->InCombat())
			{
				mGameData->mAdversary = player;
				player->InCombat(true);
				mGameData->mPlayer->InCombat(true);
				mGameData->State(ClientData::GameState::CombatStart);
			}
			else
			{
				mGameData->mOutputManager->AppendToOutput("That player is already in combat with someone else.");
			}
			break;
		}
	}
}


