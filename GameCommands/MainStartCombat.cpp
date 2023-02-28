#include "MainStartCombat.h"
#include "../GameObjects/OutputManager.h"
#include "../GameObjects/Room.h"

MainStartCombat::MainStartCombat(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainStartCombat::Execute()
{
	mGameData->mAdversary = mGameData->mRoom->GetCharacter(mArgs);
	if (mGameData->mAdversary == nullptr)
	{
		mGameData->mOutputManager->AddToOutput("The is no \"" + mArgs + "\" to fight.");
	}
	else
	{
		mGameData->mState = Game::GameState::CombatStart;
	}
}
