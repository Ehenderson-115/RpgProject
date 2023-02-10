#include "Weapon.h"


Weapon::Weapon() : Item(ClassType::Weapon, true){}

void Weapon::Damage(int input)
{
	mDamageMod = input;
}

