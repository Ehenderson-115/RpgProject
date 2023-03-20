#include "CombatDefendPlayer.h"
#include "Player.h"
#include "OutputManager.h"

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
	mGameData->mOutputManager->AppendToOutput("You prepare for an oncoming attack.");
}
