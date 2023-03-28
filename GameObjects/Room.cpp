#include "Room.h"
#include "HelperFunctions.h"
#include "Item.h"
#include "Character.h"

Room::Room() 
    : Entity(ClassType::Room)
{};


std::string Room::CheckRoomContents()
{   
    std::string output = "";
    for (int i = 0; i < mContents.size(); i++)
    {
        auto content = mContents.at(i);
        if (content->isItem() && i == 0 && output.empty())
        {
            output += "Searching around the room you found a ";
            output += content->Name();
        }
        else if (content->isItem() && i > 0) 
        {
            output += "You also found a ";
            output += content->Name();
        }
        else if (content->Type() == Entity::ClassType::Enemy && i == 0 && output.empty())
        {
            output += "There is a ";
            output += content->Name();
            output += " they don't look friendly";
        }
        else if (content->Type() == Entity::ClassType::Enemy && i > 0) 
        {
            output += "There is also a ";
            output += content->Name();
            output += " they don't look friendly";
        }
        if ((i + 1) == mContents.size()) 
        {
            output += "\n";
        }
    }
    return output;
}

std::shared_ptr<Item> Room::GetItem(std::string nameToFind)
{
    nameToFind = StrToLower(nameToFind);
    std::string currEntName;
    std::shared_ptr<Item> output = nullptr;
    for (int i = 0; i < mContents.size(); i++)
    {
        auto content = mContents.at(i);
        currEntName = content->Name();
        currEntName = StrToLower(currEntName);
        if (currEntName == nameToFind && content->isHoldable())
        {
            output = std::static_pointer_cast<Item>(content);
            mContents.erase(mContents.begin() + i);
        }
    }
    return output;
}

std::shared_ptr<Character> Room::GetCharacter(std::string nameToFind) const
{
    nameToFind = StrToLower(nameToFind);
    std::string currEntName;
    std::shared_ptr<Character> output = nullptr;
    for (auto content : mContents)
    {
        currEntName = StrToLower(content->Name());
        if (currEntName == nameToFind && !content->isHoldable())
        {
            output = std::static_pointer_cast<Character>(content);
        }
    }
    return output;
}

void Room::RemoveContent(std::string nameToFind)
{
    nameToFind = StrToLower(nameToFind);
    std::string currEntName;
    for (int i = 0; i < mContents.size(); i++)
    {
        auto content = mContents.at(i);
        currEntName = StrToLower(content->Name());
        if (currEntName == nameToFind && !content->isHoldable())
        {
            mContents.erase(mContents.begin() + i);
        }
    }
}
