#ifndef COMBAT_DEFEND_ADV_H
#define COMBAT_DEFEND_ADV_H
#include "GameCommand.h"

class CombatDefendAdversary : public GameCommand
{
public:
	CombatDefendAdversary(std::shared_ptr<ActiveGameData> inData, std::string inArgs);

	void Execute();

private:

};



#endif