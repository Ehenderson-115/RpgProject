#include "CombatAttackPlayer.h"
#include "../GameObjects/Character.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/HelperFunctions.h"

CombatAttackPlayer::CombatAttackPlayer(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};


void CombatAttackPlayer::Execute()
{
	if (mGameData->mState == Game::GameState::CombatStart)
	{
		mGameData->mState = Game::GameState::Combat;
	}
	int damageMod = (rand() % 5);
	int totalDamage;
	std::string turnDescript = "";
	std::string adversaryName = mGameData->mAdversary->Name();
	std::string wepName = mGameData->mPlayer->GetWepName();
	totalDamage = mGameData->mPlayer->Attack(damageMod);
	if (damageMod == 4)
	{
		totalDamage *= 2;
		turnDescript += ("Your " + wepName + " begins to shine brightly.");
		turnDescript += " You feel your strength increase as you let loose a devastating attack.";
		turnDescript += " Critical Hit!";
	}
	else
	{
		turnDescript += ("You ready your " + wepName + " and strike the " + adversaryName + ".");
	}
	turnDescript += (" You deal " + std::to_string(totalDamage) + " to the " + adversaryName + ".");
	mGameData->mAdversary->Damage(totalDamage);
	Game::UpdateHud(mGameData);
	FormattedPrint(turnDescript);
	if (mGameData->mAdversary->isDead())
	{
		FormattedPrint("The " + adversaryName + " has been killed.");
		FormattedPrint("Press enter to exit combat...");
	}
}
