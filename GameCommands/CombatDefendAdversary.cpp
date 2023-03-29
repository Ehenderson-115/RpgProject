#include "CombatDefendAdversary.h"
#include "Character.h"
#include "OutputManager.h"

CombatDefendAdversary::CombatDefendAdversary(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void CombatDefendAdversary::Execute()
{
	mPlayerData->mAdversary->Defend();
	mPlayerData->mOutputManager->AppendToOutput("The " + mPlayerData->mAdversary->Name() + " prepares for you to attack.");
}
