#include "Entity.h"

//Constructors
Entity::Entity() 
	: mClassType{ ClassType::Entity }
	, mHoldable{ false }
	, mItem{ false }
	, mId{ -1 }
{}

Entity::Entity(ClassType classType) 
	: mClassType{ classType }
	, mHoldable{ false }
	, mItem{ false }
	, mId{ -1 }
{}

Entity::Entity(bool holdable) 
	: mClassType{ ClassType::Entity }
	, mHoldable{ holdable }
	, mItem{ false }
	, mId{ -1 }
{}

Entity::Entity(ClassType classType, bool holdable) 
	: mClassType{ classType }
	, mHoldable{ holdable }
	, mItem{ false }
	, mId{ -1 } 
{}

Entity::Entity(ClassType classType, bool holdable, bool item) 
	: mClassType{ classType }
	, mHoldable{ holdable }
	, mItem{ item }
	, mId{ -1 } 
{}

//Setter Functions
void Entity::Id(const int& inId)
{
	mId = inId;
}

void Entity::Name(const std::string& inStr)
{
	mName = inStr;
}

void Entity::Descript(const std::string& inStr)
{
	int descriptStart = inStr.find_first_of("\"");
	descriptStart++;
	int descriptEnd = inStr.find_last_of("\"");
	descriptEnd--;

	mDescript = inStr.substr(descriptStart, descriptEnd);
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