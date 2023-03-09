#ifndef COMBAT_ATTACK_ADV_H
#define COMBAT_ATTACK_ADV_H
#include "GameCommand.h"

class CombatAttackAdversary : public GameCommand
{
public:
	CombatAttackAdversary(std::shared_ptr<ClientData> inData, std::string inArgs);

	void Execute();

private:

};



#endif