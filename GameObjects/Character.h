#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "Entity.h"


class Character : public Entity
{
public:
	Character();
	Character(ClassType classType);
	void SetRace(std::string input);
	void SetHitpoints(std::string input);
	std::string GetRace();


protected:
	std::string mRace;
	int mCurrhp;
	int mMaxhp;
};
#endif