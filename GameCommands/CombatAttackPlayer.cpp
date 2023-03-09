#include "CombatAttackPlayer.h"
#include "../GameObjects/Character.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/OutputManager.h"
CombatAttackPlayer::CombatAttackPlayer(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};


void CombatAttackPlayer::Execute()
{
	if (mGameData->State() == ClientData::GameState::CombatStart)
	{
		mGameData->mAdversary->Damage(30);
		mGameData->State(ClientData::GameState::Combat);
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
	mGameData->mOutputManager->AddToOutput(turnDescript + "\n\n");
}
