#include "CombatDefendAdversary.h"
#include "../GameObjects/Character.h"
#include "../GameObjects/OutputManager.h"

CombatDefendAdversary::CombatDefendAdversary(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void CombatDefendAdversary::Execute()
{
	mGameData->mAdversary->Defend();
	mGameData->mOutputManager->AddToOutput("The " + mGameData->mAdversary->Name() + " prepares for you to attack.");
}
