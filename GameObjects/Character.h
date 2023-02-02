#ifndef CHARACTER_H
#define CHARACTER_H
#include "Entity.h"


class Character : public Entity
{
private:


protected:
	std::string mRace;
	int mCurrhp;
	int mMaxhp;
};
#endif