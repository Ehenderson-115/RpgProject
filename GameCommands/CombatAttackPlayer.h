#ifndef COMBAT_ATTACK_PLAYER_H
#define COMBAT_ATTACK_PLAYER_H
#include "GameCommand.h"

class CombatAttackPlayer: public GameCommand
{
public:
	CombatAttackPlayer(std::shared_ptr<ClientData> inData, std::string inArgs);
	void Execute();

private:

};



#endif