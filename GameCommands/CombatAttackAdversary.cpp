#include "CombatAttackAdversary.h"
#include "../GameObjects/Character.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/HelperFunctions.h"

CombatAttackAdversary::CombatAttackAdversary(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void CombatAttackAdversary::Execute()
{
	int damageMod = (rand() % 5);
	int totalDamage;
	std::string turnDescript = "";
	std::string adversaryName = mGameData->mAdversary->Name();
	totalDamage = mGameData->mAdversary->Attack(damageMod);
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
	mGameData->mPlayer->Damage(totalDamage);

	FormattedPrint(turnDescript);
	if (mGameData->mPlayer->isDead())
	{
		FormattedPrint("You have been killed by the " + adversaryName + ".");
		FormattedPrint("Game Over. Press enter to exit...");
	};
}
