#include "CombatDefendAdversary.h"
#include "../GameObjects/Character.h"
#include "../GameObjects/HelperFunctions.h"

CombatDefendAdversary::CombatDefendAdversary(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void CombatDefendAdversary::Execute()
{
	std::string turnResult = "The " + mGameData->mAdversary->Name() + " prepares for you to attack.";
	mGameData->mAdversary->Defend();
	FormattedPrint(turnResult);
}
