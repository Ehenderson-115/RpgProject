#include "Character.h"

void Character::SetRace(std::string input)
{
	this->mRace = input;
}

void Character::SetHitpoints(std::string input)
{
	int split = input.find("/");
	split++;
	this->mCurrhp = std::stoi(input.substr(split));
	this->mMaxhp = std::stoi(input.substr(split, input.length() - size_t(1)));
}
