#include "Player.h"
#include "HelperFunctions.h"
#include "Item.h"
#include "Weapon.h"

Player::Player() : Character(ClassType::Player), mEqWeapon{ nullptr } {}

void Player::AddItem(std::shared_ptr<Item> inItem)
{
	mInventory.push_back(inItem);
}

void Player::RoomId(int inRoomId)
{
	mRoomId = inRoomId;
}

int Player::RoomId() const
{
	return mRoomId;
}

std::string Player::CheckInventory()
{
	std::string output = "";
	if(mInventory.size() == 0)
	{
		output = "Your pockets contain only dust and sadness......";
	}
	for (auto currItem : mInventory)
	{
		output += currItem->Name();
		if (mInventory.size() > 1)
		{
			output += " | ";
		}
	}
	return output;

}

std::string Player::CheckItem(std::string nameToFind) const
{
    nameToFind = StrToLower(nameToFind);
    std::string output = "";
	std::string currItemName;
    std::shared_ptr<Item> currItem = nullptr;

	for (auto currItem : mInventory)
    {
		currItemName = currItem->Name();
        currItemName = StrToLower(currItemName);
        if (currItemName == nameToFind)
        {
			output = currItem->Descript();
        }
    }
    return output;
}



void Player::EquipWeapon(std::string nameToFind)
{
	nameToFind = StrToLower(nameToFind);
	std::string output = "";
	std::string currItemName;

	for (auto currItem : mInventory)
	{
		currItemName = currItem->Name();
		currItemName = StrToLower(currItemName);
		if (currItemName == nameToFind && currItem->isEquipable())
		{
			mEqWeapon = std::static_pointer_cast<Weapon>(currItem);
		}
	}
}