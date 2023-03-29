#include "CombatDefendPlayer.h"
#include "Player.h"
#include "OutputManager.h"

CombatDefendPlayer::CombatDefendPlayer(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void CombatDefendPlayer::Execute()
{
	if (mPlayerData->State() == ClientData::GameState::CombatStart)
	{
		mPlayerData->State(ClientData::GameState::Combat);
	}

	mPlayerData->mPlayer->Defend();
	mPlayerData->mOutputManager->AppendToOutput("You prepare for an oncoming attack.");
}
