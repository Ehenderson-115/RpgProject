#include "Room.h"

Room::Room()
{
    
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
    std::string output = "You found a ";
    for (int i = 0; i < mContents.size(); i++)
    {
        if (i > 0) {
            output += " \nYou also found a ";
        }
        output += mContents.at(i)->GetName();
    }
    return output;
}

