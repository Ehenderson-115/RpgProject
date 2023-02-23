#include "Weapon.h"

Weapon::Weapon() 
	: Item(ClassType::Weapon, true)
	, mDamageMod {-1}
{}