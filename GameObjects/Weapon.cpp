#include "Weapon.h"


Weapon::Weapon() : Item(ClassType::Weapon, true){}

void Weapon::SetDamage(int input)
{
	mBaseDamage = input;
}

