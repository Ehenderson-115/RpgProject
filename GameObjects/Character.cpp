#include "Character.h"
#include "Entity.h"

Character::Character() : Entity(ClassType::Character) {}
Character::Character(ClassType classType) : Entity(classType) {}

void Character::SetRace(std::string input)
{
	mRace = input;
}

void Character::SetHitpoints(std::string input)
{
	int split = input.find("/");
	split++;
	mCurrhp = std::stoi(input.substr(split));
	mMaxhp = std::stoi(input.substr(split, input.length() - size_t(1)));
}

std::string Character::GetRace()
{
	return mRace;
}
