#include "Entity.h"

Entity::Entity()
{
	mClassType = "entity";
	mHoldable = false;
}

void Entity::SetId(int input)
{
	mId = input;
}

void Entity::SetName(std::string input)
{
	mName = input;
}

void Entity::SetDescript(std::string input)
{
	int descriptStart = input.find_first_of("\"");
	descriptStart++;
	int descriptEnd = input.find_last_of("\"");
	descriptEnd--;

	mDescript = input.substr(descriptStart, descriptEnd);
}

int Entity::GetId()
{
	return mId;
}

std::string Entity::GetName()
{
	return mName;
}

std::string Entity::GetClassType()
{
	return mClassType;
}

bool Entity::isHoldable()
{
	return mHoldable;
}



std::string Entity::GetDescript()
{
	return mDescript;
}

