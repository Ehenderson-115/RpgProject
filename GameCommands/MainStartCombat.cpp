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
	//std::lock_guard<std::mutex> lock(mPlayerData->mMutex);
	auto adversary = mPlayerData->mRoom->GetCharacter(mArgs);
	if (adversary == nullptr)
	{
		SafelyAddPlayerAdv();
		if (mPlayerData->mAdversary == nullptr)
		{
			mPlayerData->mOutputManager->AppendToOutput("The is no \"" + mArgs + "\" to fight.");
		}
	}
	else
	{
		if (adversary->InCombat())
		{
			mPlayerData->mOutputManager->AppendToOutput("That target is already in combat with someone else.");
		}
		else
		{
			mPlayerData->mPlayer->InCombat(true);
			adversary->InCombat(true);
			mPlayerData->State(ClientData::GameState::CombatStart);
		}
	}
}

void MainStartCombat::SafelyAddPlayerAdv()
{
	for (auto player : mPlayerData->mWorld->GetOtherPlayers(mPlayerData->mPlayer))
	{
		if ((StrToLower(mArgs) == StrToLower(player->Name()) && (mPlayerData->mWorld->GetPlayerLoc(player) == mPlayerData->mRoom)))
		{
			if (!player->InCombat())
			{
				mPlayerData->mAdversary = player;
				player->InCombat(true);
				mPlayerData->mPlayer->InCombat(true);
				mPlayerData->State(ClientData::GameState::CombatStart);
				mPlayerData->mOutputManager->AppendToOutput("Waiting for other player...");
			}
			else
			{
				mPlayerData->mOutputManager->AppendToOutput("That player is already in combat with someone else.");
			}
			break;
		}
	}
}


