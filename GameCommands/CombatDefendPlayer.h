#ifndef COMBAT_DEFEND_PLAYER_H
#define COMBAT_DEFEND_PLAYER_H
#include "GameCommand.h"

class CombatDefendPlayer : public GameCommand
{
public:
	CombatDefendPlayer(std::shared_ptr<ClientData> inData, std::string inArgs);
	void Execute();

private:

};



#endif