#include "Room.h"


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

