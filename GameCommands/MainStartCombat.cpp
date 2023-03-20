#include "MainStartCombat.h"
#include "OutputManager.h"
#include "Room.h"

MainStartCombat::MainStartCombat(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MainStartCombat::Execute()
{
	mGameData->mAdversary = mGameData->mRoom->GetCharacter(mArgs);
	if (mGameData->mAdversary == nullptr)
	{
		mGameData->mOutputManager->AppendToOutput("The is no \"" + mArgs + "\" to fight.");
	}
	else
	{
		mGameData->State(ClientData::GameState::CombatStart);
	}
}
