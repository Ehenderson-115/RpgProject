#ifndef ITEM_H
#define ITEM_H
#include "Entity.h"

class Item : public Entity{
public:
	Item();
	Item(ClassType classType, bool equipable);

	bool isEquipable() const;
	
protected:


	bool mEquipable;
};
#endif