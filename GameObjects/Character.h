#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "Entity.h"

class Character : public Entity
{
public:
	enum class CharRace { Unknown, Human, Orc, Elf, Dwarf, Tiefling, Halfling };
	Character();
	Character(ClassType classType);
	
	int HitPoints() const;
	void Hitpoints(std::string inStr);

	CharRace Race() const;
	void Race(std::string inStr);
	void Race(CharRace inRace);

	CharRace TranslateRace(std::string inStr);
	std::string TranslateRace(CharRace inRace);

protected:
	CharRace mRace;
	int mCurrhp;
	int mMaxhp;
};
#endif