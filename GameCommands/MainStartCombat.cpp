#include "MainStartCombat.h"
#include "../GameObjects/HelperFunctions.h"
#include "../GameObjects/Room.h"

MainStartCombat::MainStartCombat(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainStartCombat::Execute()
{
	mGameData->mAdversary = mGameData->mRoom->GetCharacter(mArgs);
	if (mGameData->mAdversary == nullptr)
	{
		FormattedPrint("The is no \"" + mArgs + "\" to fight.");
	}
	else
	{
		mGameData->mState = Game::GameState::CombatStart;
	}
}
