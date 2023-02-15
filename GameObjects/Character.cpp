#include "Character.h"
#include "Entity.h"

Character::Character() 
	: Entity(ClassType::Character)
	, mRace{ CharRace::Unknown }
	, mCurrAction{ Action::Idle }
	, mCurrhp{ 0 }, mMaxhp{ 0 }
	, mBaseAttack{ 0 } 
{}

Character::Character(ClassType classType) 
	: Entity(classType)
	, mRace{ CharRace::Unknown }
	, mCurrAction{ Action::Idle }
	, mCurrhp{ 0 }
	, mMaxhp{ 0 }
	, mBaseAttack{ 0 }
{}

int Character::HitPoints() const
{
	return mCurrhp;
}

void Character::Hitpoints(const std::string& inStr)
{
	int split = inStr.find("/");
	split++;
	mCurrhp = std::stoi(inStr.substr(split));
	mMaxhp = std::stoi(inStr.substr(split, inStr.length() - size_t(1)));
}

Character::CharRace Character::Race() const
{
	return mRace;
}

void Character::Race(const std::string& inStr)
{
	mRace = TranslateRace(inStr);
}

void Character::Race(const CharRace& inRace)
{
	mRace = inRace;
}

Character::CharRace Character::TranslateRace(const std::string& inStr)
{
	if(inStr == "human")
	{ 
		return CharRace::Human;
	}
	else if (inStr == "orc")
	{
		return CharRace::Orc;
	}
	else if (inStr == "elf")
	{
		return CharRace::Elf;
	}
	else if (inStr == "tiefling")
	{
		return CharRace::Tiefling;
	}
	else if (inStr == "halfling")
	{
		return CharRace::Halfling;
	}
	else
	{
		return CharRace::Unknown;
	}
}

std::string Character::TranslateRace(const CharRace& inRace)
{
	switch (inRace)
	{
	case CharRace::Human:
		return "Human";
	case CharRace::Orc:
		return "Orc";
	case CharRace::Elf:
		return "Elf";
	case CharRace::Tiefling:
		return "Tiefling";
	case CharRace::Halfling:
		return "Halfling";
	default:
		return "Unknown";
	}
}

void Character::BaseAttack(int inAttackStat)
{
	mBaseAttack = inAttackStat;
}

Character::Action Character::CurrAction() const
{
	return mCurrAction;
}

void Character::Damage(const int& damageTaken)
{
	if (mCurrAction == Action::Defending)
	{
		mCurrhp -= (damageTaken / 2);
	}
	else 
	{
		mCurrhp -= damageTaken;
	}
	if (mCurrhp < 0)
	{
		mCurrhp = 0;
	}
}

int Character::Attack(const int& modifier)
{
	mCurrAction = Action::Attacking;
	return (mBaseAttack + modifier);
}

void Character::Defend()
{
	mCurrAction = Action::Defending;
}

std::string Character::GetStatus() const
{
	std::string output = "";
	output += mName;
	output += "|";
	output += (std::to_string(mCurrhp) + "/" + std::to_string(mMaxhp));
	return output;
}

bool Character::isDead() const
{
	return (mCurrhp <= 0);
}