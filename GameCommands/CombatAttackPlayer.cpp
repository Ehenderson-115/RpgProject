#include "CombatAttackPlayer.h"
#include "Character.h"
#include "Player.h"
#include "OutputManager.h"
CombatAttackPlayer::CombatAttackPlayer(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};


void CombatAttackPlayer::Execute()
{
	if (mPlayerData->State() == ClientData::GameState::CombatStart)
	{
		mPlayerData->mAdversary->Damage(30);
		mPlayerData->State(ClientData::GameState::Combat);
	}
	int damageMod = (rand() % 5);
	int totalDamage;
	std::string turnDescript = "";
	std::string adversaryName = mPlayerData->mAdversary->Name();
	std::string wepName = mPlayerData->mPlayer->GetWepName();
	totalDamage = mPlayerData->mPlayer->Attack(damageMod);
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
	mPlayerData->mAdversary->Damage(totalDamage);
	mPlayerData->mOutputManager->AppendToOutput(turnDescript + "\n\n");

}
