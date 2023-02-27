#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "Character.h"


class Item;
class Weapon;
class Room;

class Player : public Character
{
public:
	Player();
	Player(std::string inName);

	//Getters
	std::string CheckInventory();
	std::string CheckItem(std::string nameToFind) const;
	std::string EquipWeapon(std::string nameToFind);
	std::string GetStatus() const;
	std::string GetWepName() const;

	//Setters
	void AddItem(const std::shared_ptr<Item>& inItem) { mInventory.push_back(inItem); }

	int Attack(const int& modifier);

private:
	std::shared_ptr<Weapon> mEqWeapon;
	std::vector<std::shared_ptr<Item>> mInventory;
	
};
#endif