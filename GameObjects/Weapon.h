#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"

class Weapon : public Item
{
public:
	void SetDamage(int input);

private:
	int mBaseDamage;

};
#endif