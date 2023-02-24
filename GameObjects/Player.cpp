#include "Player.h"
#include "HelperFunctions.h"
#include "Item.h"
#include "Weapon.h"

Player::Player() 
	: Character(ClassType::Player)
	, mEqWeapon{ nullptr } 
{}

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
    std::string output = "Hours pass and you still the haven't found the \"" + nameToFind + "\" that you were looking for...";
	std::string currItemName;

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

std::string Player::EquipWeapon(std::string nameToFind)
{
	nameToFind = StrToLower(nameToFind);
	std::string output = "Equipping the \"" + nameToFind + "\" is impossible...what were you thinking???";
	std::string currItemName;

	for (auto currItem : mInventory)
	{
		currItemName = currItem->Name();
		currItemName = StrToLower(currItemName);
		if (currItemName == nameToFind && currItem->isEquipable())
		{
			mEqWeapon = std::static_pointer_cast<Weapon>(currItem);
			output = "You equipped the " + currItem->Name() + ". You swing it a few times before resting it on your right shoulder with a flourish.";
		}
	}
	return output;
}

std::string Player::GetStatus() const
{
	std::string output = "";
	output += mName;
	output += " | ";
	output += (std::to_string(mCurrhp) + "/" + std::to_string(mMaxhp));
	output += " | ";
	if (mEqWeapon != nullptr)
	{
		output += mEqWeapon->Name();
	}
	else 
	{
		output += "Bare Hands";
	}

	return output;
}

int Player::Attack(const int& modifier)
{
	mCurrAction = Action::Attacking;
	int output = (mBaseAttack + modifier);
	if (mEqWeapon != nullptr)
	{
		output += mEqWeapon->Damage();
	}
	return output;
}

std::string Player::GetWepName() const
{
	if (mEqWeapon == nullptr)
	{
		return "Bare Hands";
	}
	else
	{
		return mEqWeapon->Name();
	}
}