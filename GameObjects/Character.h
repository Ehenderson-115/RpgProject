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
	Character(ClassType classType, std::string inName);

	//Getters
	std::string GetStatus() const;
	int HitPoints() const { return mCurrhp; }
	CharRace Race() const { return mRace; }

	//Setters
	void Hitpoints(const std::string& inStr);
	void Race(const std::string& inStr) { mRace = TranslateRace(inStr); }
	void Race(const CharRace& inRace) { mRace = inRace; }
	void BaseAttack(int inAttackStat) { mBaseAttack = inAttackStat; }
	
	//Combat Functions
	Action CurrAction() const { return mCurrAction; }
	void Damage(int damageTaken);
	void Heal(int hpRestored);
	int Attack(int modifier);
	void Defend() { mCurrAction = Action::Defending; }
	
	bool isDead() const { return (mCurrhp <= 0); }

	bool InCombat() const { return mCombatFlag; }
	bool InCombat(bool input) { mCombatFlag = input; }

protected:	
	CharRace TranslateRace(const std::string& inStr);
	std::string TranslateRace(const CharRace& inRace);
	CharRace mRace;
	Action mCurrAction;
	int mBaseAttack;
	int mCurrhp;
	int mMaxhp;
	bool mCombatFlag;
};
#endif