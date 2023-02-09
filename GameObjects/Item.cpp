#include "Item.h"

Item::Item() : Entity(ClassType::Item, true), mEquipable{false} {}

Item::Item(ClassType classType, bool equipable) : Entity(classType, true), mEquipable{ equipable }{}

bool Item::isEquipable() const
{
	return mEquipable;
}