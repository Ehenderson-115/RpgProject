#include "Room.h"
#include "HelperFunctions.h"

Room::Room()
{
    mClassType = ClassType::Room;
    mHoldable = false;

}

void Room::AddRoomObject(std::shared_ptr<Entity> inEntity)
{
    mContents.push_back(inEntity);
}

void Room::AddRoomConnection(int input, char direction)
{
    switch (direction)
    {
    case('n'):
        mNorthId = input;
        break;
    case('s'):
        mSouthId = input;
        break;
    case('e'):
        mEastId = input;
        break;
    case('w'):
        mWestId = input;
        break;
    default:
        std::cout << "Error Invaild Direction passed to AddRoomConnection()" << std::endl;
    }
}

std::string Room::CheckRoomContents()
{   
    std::string output = "You searched the room found a ";
    for (int i = 0; i < mContents.size(); i++)
    {
        if (i > 0) {
            output += " \nYou also found a ";
        }
        output += mContents.at(i)->Name();
    }
    return output;
}

std::shared_ptr<Item> Room::GetItem(std::string nameToFind)
{
    StrToLower(nameToFind);
    std::string currEntName;
    std::shared_ptr<Item> output = nullptr;
    std::shared_ptr<Entity> currEnt = nullptr;
    for (int i = 0; i < mContents.size(); i++)
    {
        currEnt = mContents.at(i);
        currEntName = currEnt->Name();
        StrToLower(currEntName);
        if (currEntName == nameToFind && currEnt->isHoldable())
        {
            output = std::static_pointer_cast<Item>(currEnt);
            mContents.erase(mContents.begin() + i);
        }
    }
    return output;
}

int Room::GetRoom(std::string inStr)
{
    char direction = TranslateDirection(inStr);
    switch(direction)
    {
    case('n'):
        return mNorthId;
        break;
    case('s'):
        return mSouthId;
        break;
    case('e'):
        return mEastId;
        break;
    case('w'):
        return mWestId;
        break;
    default:
        PrintString("Invaid direction: " + inStr);
        return NULL;
    }
}


char Room::TranslateDirection(std::string inStr)
{
    StripString(inStr, " ");
    StrToLower(inStr);

    if (inStr == "north" || inStr == "n")
    {
        return 'n';
    }
    else if (inStr == "south" || inStr == "s")
    {
        return 's';
    }
    else if (inStr == "east" || inStr == "e")
    {
        return 'e';
    }
    else if (inStr == "west" || inStr == "w")
    {
        return 'w';
    }
    else
    {
        return NULL;
    }

}
