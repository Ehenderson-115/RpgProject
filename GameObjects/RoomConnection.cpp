#include "RoomConnection.h"
#include "HelperFunctions.h"

RoomConnection::RoomConnection(std::shared_ptr<Room> inMainRoom
	, std::shared_ptr<Room> inConnectedRoom
	, Direction inConnectionDir)
	: mMainRoom {inMainRoom}
	, mConnectedRoom {inConnectedRoom}
	, mConnectionDir { inConnectionDir }
{}

RoomConnection::Direction RoomConnection::GetOpposite(const Direction& inDir)
{
    switch (inDir)
    {
    case RoomConnection::Direction::North:
        return RoomConnection::Direction::South;
        break;
    case RoomConnection::Direction::South:
        return RoomConnection::Direction::North;
        break;
    case RoomConnection::Direction::East:
        return RoomConnection::Direction::West;
        break;
    case RoomConnection::Direction::West:
        return RoomConnection::Direction::East;
        break;
    default:
        return RoomConnection::Direction::Invalid;
        break;
    }
}

RoomConnection::Direction RoomConnection::TranslateDirection(std::string inStr)
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

std::string RoomConnection::TranslateDirection(const RoomConnection::Direction& inDir)
{
    switch (inDir)
    {
    case RoomConnection::Direction::North:
        return "north";
        break;
    case RoomConnection::Direction::South:
        return "south";
        break;
    case RoomConnection::Direction::East:
        return "east";
        break;
    case RoomConnection::Direction::West:
        return "west";
        break;
    default:
        return "invalid";
        break;
    }
}