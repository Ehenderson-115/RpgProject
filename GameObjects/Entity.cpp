#include "Entity.h"

void Entity::SetId(int input)
{
	this->mId = input;
}

void Entity::SetDescript(std::string input)
{
	int descriptStart = input.find_first_of("\"");
	descriptStart++;
	int descriptEnd = input.find_last_of("\"");
	descriptEnd--;

	this->mDescript = input.substr(descriptStart, descriptEnd);
}

void Entity::SetName(std::string input)
{
	this->mName = input;
}
