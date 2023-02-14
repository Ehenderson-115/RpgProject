#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "Entity.h"

class Character : public Entity
{
public:
	enum class CharRace { Unknown, Human, Orc, Elf, Dwarf, Tiefling, Halfling };
	enum class Action { Idle, Attacking, Defending};
	Character();
	Character(ClassType classType);
	
	int HitPoints() const;
	void Hitpoints(const std::string& inStr);

	CharRace Race() const;
	void Race(const std::string& inStr);
	void Race(const CharRace& inRace);

	CharRace TranslateRace(const std::string& inStr);
	std::string TranslateRace(const CharRace& inRace);

	void BaseAttack(int inAttackStat);
	
	//Combat Actions
	Action CurrAction() const;
	void Damage(const int& damageTaken);
	int Attack(const int& modifier);
	void Defend();
	
	std::string GetStatus() const;

	bool isDead() const;


protected:
	CharRace mRace;
	Action mCurrAction;
	int mBaseAttack;
	int mCurrhp;
	int mMaxhp;
};
#endif