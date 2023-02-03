#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "Character.h"


class Item;

class Player : public Character
{
public:
	
private:
	std::vector<std::shared_ptr<Entity>> inventory;
	
};
#endif // !PLAYER_H