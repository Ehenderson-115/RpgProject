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

	//Getters
	int RoomId() const { return mRoomId; }
	std::shared_ptr<Room> Location() const { return mCurrRoom; }
	std::string CheckInventory();
	std::string CheckItem(std::string nameToFind) const;
	std::string EquipWeapon(std::string nameToFind);
	std::string GetStatus() const;
	std::string GetWepName() const;

	//Setters
	void RoomId(const int& inRoomId) {mRoomId = inRoomId;}
	void Location(std::shared_ptr<Room> inRoom) { mCurrRoom = inRoom; }
	void AddItem(const std::shared_ptr<Item>& inItem) { mInventory.push_back(inItem); }

	int Attack(const int& modifier);

private:
	int mRoomId;
	std::shared_ptr<Room> mCurrRoom;
	std::shared_ptr<Weapon> mEqWeapon;
	std::vector<std::shared_ptr<Item>> mInventory;
	
};
#endif