#include "Entity.h"

//Constructors
Entity::Entity() : mClassType{ ClassType::Entity }, mHoldable{ false }, mItem{ false }, mId{ -1 }{}
Entity::Entity(ClassType classType) : mClassType{ classType }, mHoldable{ false }, mItem{ false }, mId{ -1 } {}
Entity::Entity(bool holdable) : mClassType{ ClassType::Entity }, mHoldable{ holdable }, mItem{ false }, mId{ -1 } {}
Entity::Entity(ClassType classType, bool holdable) : mClassType{ classType }, mHoldable{ holdable }, mItem{ false }, mId{ -1 } {}
Entity::Entity(ClassType classType, bool holdable, bool item) : mClassType{ classType }, mHoldable{ holdable }, mItem{ item }, mId{ -1 } {}

//Setter Functions
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

//Getter Functions
int Entity::Id() const
{
	return mId;
}

Entity::ClassType Entity::classType() const
{
	return mClassType;
}

std::string Entity::Name() const
{
	return mName;
}

bool Entity::isHoldable() const
{
	return mHoldable;
}

bool Entity::isItem() const
{
	return mItem;
}

std::string Entity::Descript() const
{
	return mDescript;
}