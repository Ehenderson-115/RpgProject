#include "Character.h"
#include "Entity.h"

Character::Character() : Entity(ClassType::Character), mRace{ CharRace::Unknown }, mCurrhp{ 0 }, mMaxhp{ 0 } {}
Character::Character(ClassType classType) : Entity(classType), mRace{ CharRace::Unknown }, mCurrhp{ 0 }, mMaxhp{ 0 }{}

int Character::HitPoints() const
{
	return mCurrhp;
}

void Character::Hitpoints(std::string input)
{
	int split = input.find("/");
	split++;
	mCurrhp = std::stoi(input.substr(split));
	mMaxhp = std::stoi(input.substr(split, input.length() - size_t(1)));
}

Character::CharRace Character::Race() const
{
	return mRace;
}

void Character::Race(std::string inStr)
{
	mRace = TranslateRace(inStr);
}

void Character::Race(CharRace inRace)
{
	mRace = inRace;
}

Character::CharRace Character::TranslateRace(std::string inStr)
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

std::string Character::TranslateRace(CharRace inRace)
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