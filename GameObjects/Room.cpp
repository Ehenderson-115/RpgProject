#include "Room.h"

std::string Room::GetDescript()
{
    return mDescript;
}

void Room::AddCharacter(std::shared_ptr<Character> inCharacter)
{
    mCharacters.push_back(inCharacter);
}

void Room::AddRoomObject(std::shared_ptr<Entity> inEntity)
{
    mContents.push_back(inEntity);
}

void Room::AddRoomConnection(std::shared_ptr<Room> inRoom, char direction)
{
    switch (direction) \
    {
    case('n'):
        mNorth = inRoom;
        break;
    case('s'):
        mSouth = inRoom;
        break;
    case('e'):
        mEast = inRoom;
        break;
    case('w'):
        mWest = inRoom;
        break;
    default:
        std::cout << "Error Invaild Direction passed to AddRoomConnection()" << std::endl;
    }
}

