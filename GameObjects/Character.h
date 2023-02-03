#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "Entity.h"


class Character : public Entity
{
public:
	void SetRace(std::string input);
	void SetHitpoints(std::string input);


protected:
	std::string mRace;
	int mCurrhp;
	int mMaxhp;
};
#endif