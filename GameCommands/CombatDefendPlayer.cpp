#include "CombatDefendPlayer.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/OutputManager.h"

CombatDefendPlayer::CombatDefendPlayer(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void CombatDefendPlayer::Execute()
{
	if (mGameData->State() == ClientData::GameState::CombatStart)
	{
		mGameData->State(ClientData::GameState::Combat);
	}

	mGameData->mPlayer->Defend();
	mGameData->mOutputManager->AddToOutput("You prepare for an oncoming attack.");
}
