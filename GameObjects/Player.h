#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "Character.h"


class Item;
class Weapon;

class Player : public Character
{
public:
	Player();
	
	int RoomId() const;
	void RoomId(int inRoomId);

	std::string CheckInventory();
	std::string CheckItem(std::string nameToFind) const;
	
	void AddItem(std::shared_ptr<Item> inItem);
	
	void EquipWeapon(std::string nameToFind);

private:
	int mRoomId;
	std::shared_ptr<Weapon> mEqWeapon;
	std::vector<std::shared_ptr<Item>> mInventory;
	
};
#endif