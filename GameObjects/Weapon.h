#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"

class Weapon : public Item
{
public:
	Weapon();

	void Damage(int input);

private:
	int mDamageMod;

};
#endif