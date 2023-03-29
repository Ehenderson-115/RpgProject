#include "CombatAttackAdversary.h"
#include "Character.h"
#include "Player.h"
#include "OutputManager.h"

CombatAttackAdversary::CombatAttackAdversary(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void CombatAttackAdversary::Execute()
{
	int damageMod = (rand() % 5);
	int totalDamage;
	std::string turnDescript = "";
	std::string adversaryName = mPlayerData->mAdversary->Name();
	totalDamage = mPlayerData->mAdversary->Attack(damageMod);
	if (damageMod == 4)
	{
		totalDamage *= 2;
		turnDescript += ("The " + adversaryName + " begins to glow.");
		turnDescript += " They strike you with double the strength they had previously.";
	}
	else
	{
		turnDescript += ("The " + adversaryName + " attacks you.");
	}
	turnDescript += " You take " + std::to_string(totalDamage) + " points of damage.";
	mPlayerData->mPlayer->Damage(totalDamage);
	mPlayerData->mOutputManager->AppendToOutput(turnDescript);
}
