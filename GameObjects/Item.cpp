#include "Item.h"

Item::Item()
{
	mClassType = "item";
	mHoldable = true;
	mEquipable = false;
}

bool Item::isEquipable()
{
	return mEquipable;
}