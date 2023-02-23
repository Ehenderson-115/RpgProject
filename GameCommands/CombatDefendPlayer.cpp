#include "CombatDefendPlayer.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/HelperFunctions.h"

CombatDefendPlayer::CombatDefendPlayer(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void CombatDefendPlayer::Execute()
{
	if (mGameData->mState == Game::GameState::CombatStart)
	{
		mGameData->mState = Game::GameState::Combat;
	}
	std::string turnResult = "You prepare for an oncoming attack.";
	mGameData->mPlayer->Defend();
	FormattedPrint(turnResult);
}
