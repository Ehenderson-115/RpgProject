#ifndef ITEM_H
#define ITEM_H
#include "Entity.h"

class Item : public Entity{
public:
	Item();
	bool isEquipable();
	
protected:


	bool mEquipable;
};
#endif