#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"

class Weapon : public Item
{
public:
	Weapon();

	//Getters
	int Damage() const { return mDamageMod; }
	
	//Setters
	void Damage(int inDmg) { mDamageMod = inDmg; }
	

private:
	int mDamageMod;

};
#endif