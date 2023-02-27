#include "Connection.h"
#include "HelperFunctions.h"

Connection::Connection(std::shared_ptr<Room> inMainRoom
	, std::shared_ptr<Room> inConnectedRoom
	, Direction inConnectionDir)
	: mMainRoom {inMainRoom}
	, mConnectedRoom {inConnectedRoom}
	, mConnectionDir { inConnectionDir }
{}

Connection::Direction Connection::GetOpposite(const Direction& inDir)
{
    switch (inDir)
    {
    case Connection::Direction::North:
        return Connection::Direction::South;
        break;
    case Connection::Direction::South:
        return Connection::Direction::North;
        break;
    case Connection::Direction::East:
        return Connection::Direction::West;
        break;
    case Connection::Direction::West:
        return Connection::Direction::East;
        break;
    case Connection::Direction::Invalid:
        return Connection::Direction::Invalid;
        break;
    }
}

Connection::Direction Connection::TranslateDirection(std::string inStr)
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

std::string Connection::TranslateDirection(const Connection::Direction& inDir)
{
    switch (inDir)
    {
    case Connection::Direction::North:
        return "north";
        break;
    case Connection::Direction::South:
        return "south";
        break;
    case Connection::Direction::East:
        return "east";
        break;
    case Connection::Direction::West:
        return "west";
        break;
    case Connection::Direction::Invalid:
        return "invalid";
        break;
    }
}