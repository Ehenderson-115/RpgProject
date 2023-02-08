#include "Weapon.h"


Weapon::Weapon()
{
	mClassType = "weapon";
	mHoldable = true;
	mEquipable = true;
}

void Weapon::SetDamage(int input)
{
	this->mBaseDamage = input;
}

