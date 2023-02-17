#include "Room.h"
#include "HelperFunctions.h"
#include "Item.h"
#include "Character.h"

Room::Room() 
    : Entity(ClassType::Room)
    , mNorthId{ -1 }
    , mSouthId{ -1 }
    , mEastId{ -1 }
    , mWestId{ -1 } 
    , mNorth{ nullptr }
    , mSouth{ nullptr }
    , mEast{ nullptr }
    , mWest{ nullptr }
{};

std::shared_ptr<Room> Room::North() const
{
    return mNorth;
}

std::shared_ptr<Room> Room::South() const
{
    return mSouth;
}

std::shared_ptr<Room> Room::East() const
{
    return mEast;
}

std::shared_ptr<Room> Room::West() const
{
    return mWest;
}

void Room::North(std::shared_ptr<Room> inRoom)
{
    mNorth = inRoom;
}

void Room::South(std::shared_ptr<Room> inRoom)
{
    mSouth = inRoom;
}

void Room::East(std::shared_ptr<Room> inRoom)
{
    mEast = inRoom;
}

void Room::West(std::shared_ptr<Room> inRoom)
{
    mWest = inRoom;
}



void Room::AddRoomObject(std::shared_ptr<Entity> inEntity)
{
    mContents.push_back(inEntity);
}

void Room::RoomId(int roomId, Direction inDir)
{
    switch (inDir)
    {
    case Direction::North:
        mNorthId = roomId;
        break;
    case Direction::South:
        mSouthId = roomId;
        break;
    case Direction::East:
        mEastId = roomId;
        break;
    case Direction::West:
        mWestId = roomId;
        break;
    }
}

void Room::RoomId(int roomId, const std::string& inStr)
{
    RoomId(roomId, TranslateDirection(inStr));
}

int Room::RoomId(const std::string& inStr)
{
    return RoomId(TranslateDirection(inStr));
}

int Room::RoomId(const Direction& inDir) const
{
    switch(inDir)
    {
    case Direction::North:
        return mNorthId;
        break;
    case Direction::South:
        return mSouthId;
        break;
    case Direction::East:
        return mEastId;
        break;
    case Direction::West:
        return mWestId;
        break;
    default:
        return NULL;
    }
}

std::shared_ptr<Room> Room::ConnectedRoom(const std::string& inStr)
{
    return ConnectedRoom(TranslateDirection(inStr));
}

std::shared_ptr<Room> Room::ConnectedRoom(const Direction& inDir) const
{
    switch (inDir)
    {
    case Direction::North:
        return mNorth;
        break;
    case Direction::South:
        return mSouth;
        break;
    case Direction::East:
        return mEast;
        break;
    case Direction::West:
        return mWest;
        break;
    default:
        return nullptr;
    }
}

Room::Direction Room::TranslateDirection(std::string inStr)
{
    inStr = StripString(inStr, " ");
    inStr = StrToLower(inStr);

    if (inStr == "north" || inStr == "n")
    {
        return Direction::North;
    }
    else if (inStr == "south" || inStr == "s")
    {
        return Direction::South;
    }
    else if (inStr == "east" || inStr == "e")
    {
        return Direction::East;
    }
    else if (inStr == "west" || inStr == "w")
    {
        return Direction::West;
    }
    else
    {
        return Direction::Invalid;
    }

}

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
        else if (content->classType() == Entity::ClassType::Enemy && i == 0 && output.empty())
        {
            output += "There is a ";
            output += content->Name();
            output += " they don't look friendly";
        }
        else if (content->classType() == Entity::ClassType::Enemy && i > 0) 
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
    if (output.empty())
    {
        output += "There is nothing of interest in this room";
        output += "\n";
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
