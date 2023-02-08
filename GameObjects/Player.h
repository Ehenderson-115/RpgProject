#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "Character.h"
#include "Room.h"
#include "Item.h"
#include "Weapon.h"


class Player : public Character
{
public:
	Player();
	
	std::string CheckInventory();
	std::string CheckItem(std::string nameToFind);
	int GetCurrRoomId();
	
	void AddItem(std::shared_ptr<Item> inItem);
	void SetCurrRoomId(int inRoomId);

	void EquipWeapon(std::string nameToFind);

private:
	int mCurrRoomId;
	std::shared_ptr<Weapon> mCurrWeapon;
	std::vector<std::shared_ptr<Item>> mInventory;
	
};
#endif