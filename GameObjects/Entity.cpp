#include "Entity.h"
#include "HelperFunctions.h"

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

std::string Entity::StripQuotes(std::string inStr)
{
	return StripString(inStr, "\"");
}
