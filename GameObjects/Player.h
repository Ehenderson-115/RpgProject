#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Character.h"


class Item;

class Player : public Character
{
public:
	
private:

	std::vector<Item> inventory;
	
};
#endif // !PLAYER_H