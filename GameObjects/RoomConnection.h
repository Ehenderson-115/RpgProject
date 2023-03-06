#ifndef ROOM_CONNECTION_H
#define ROOM_CONNECTION_H
#include <string>
#include <memory>

class Room;

struct RoomConnection 
{
	enum class Direction { North, South, East, West, Invalid };
	RoomConnection(std::shared_ptr<Room> inRoom1
		, std::shared_ptr<Room> inRoom2
		, Direction inConnectionDir);

	std::shared_ptr<Room> mMainRoom;
	std::shared_ptr<Room> mConnectedRoom;
	Direction mConnectionDir;

	static Direction GetOpposite(const Direction& inDir);
	static Direction TranslateDirection(std::string inStr);
	static std::string TranslateDirection(const Direction& inDir);
};


#endif