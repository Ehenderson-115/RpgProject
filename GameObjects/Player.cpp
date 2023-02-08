#include "Player.h"

Player::Player()
{
	mClassType = "player";
	mHoldable = false;
}

void Player::AddItem(std::shared_ptr<Item> inItem)
{
	mInventory.push_back(inItem);
}

void Player::SetCurrRoomId(int inRoomId)
{
	mCurrRoomId = inRoomId;
}

std::string Player::CheckInventory()
{
	std::string output = "";
	std::shared_ptr<Item> currItem = nullptr;
	if(mInventory.size() == 0)
	{
		output = "Your pockets contain only dust and sadness......";
	}
	for (int i = 0; i < mInventory.size(); i++)
	{
		currItem = mInventory.at(i);
		output += currItem->GetName();
		if (mInventory.size() > 1)
		{
			output += " | ";
		}
	}
	return output;

}

std::string Player::CheckItem(std::string nameToFind)
{
    StrToLower(nameToFind);
    std::string output = "";
	std::string currItemName;
    std::shared_ptr<Item> currItem = nullptr;

    for (int i = 0; i < mInventory.size(); i++)
    {
        currItem = mInventory.at(i);
		currItemName = currItem->GetName();
        StrToLower(currItemName);
        if (currItemName == nameToFind)
        {
			output = currItem->GetDescript();
        }
    }
    return output;
}

int Player::GetCurrRoomId()
{
	return mCurrRoomId;
}

void Player::EquipWeapon(std::string nameToFind)
{
	StrToLower(nameToFind);
	std::string output = "";
	std::string currItemName;
	std::shared_ptr<Item> currItem = nullptr;

	for (int i = 0; i < mInventory.size(); i++)
	{
		currItem = mInventory.at(i);
		currItemName = currItem->GetName();
		StrToLower(currItemName);
		if (currItemName == nameToFind && currItem->isEquipable())
		{
			output = currItem;
		}
	}
	return output;
}