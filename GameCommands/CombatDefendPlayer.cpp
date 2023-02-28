#include "CombatDefendPlayer.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/OutputManager.h"

CombatDefendPlayer::CombatDefendPlayer(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void CombatDefendPlayer::Execute()
{
	if (mGameData->mState == Game::GameState::CombatStart)
	{
		mGameData->mState = Game::GameState::Combat;
	}

	mGameData->mPlayer->Defend();
	mGameData->mOutputManager->AddToOutput("You prepare for an oncoming attack.");
}
