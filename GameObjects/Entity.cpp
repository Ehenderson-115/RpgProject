#include "Entity.h"

//Constructors
Entity::Entity() : mClassType{ ClassType::Entity }, mHoldable{ false } {}
Entity::Entity(ClassType classType) : mClassType{ classType } {}
Entity::Entity(bool holdable) : mHoldable{ holdable } {}
Entity::Entity(ClassType classType, bool holdable) : mClassType{ classType }, mHoldable{ holdable } {}

//Getter Functions
void Entity::Id(int input)
{
	mId = input;
}

void Entity::Name(std::string input)
{
	mName = input;
}

void Entity::Descript(std::string input)
{
	int descriptStart = input.find_first_of("\"");
	descriptStart++;
	int descriptEnd = input.find_last_of("\"");
	descriptEnd--;

	mDescript = input.substr(descriptStart, descriptEnd);
}


//Setter Functions
int Entity::Id() const
{
	return mId;
}

std::string Entity::Name() const
{
	return mName;
}

bool Entity::isHoldable() const
{
	return mHoldable;
}

std::string Entity::Descript() const
{
	return mDescript;
}

