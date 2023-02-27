#ifndef CONNECTION_H
#define CONNECTION_H
#include <string>
#include <memory>

class Room;

struct Connection 
{
	enum class Direction { North, South, East, West, Invalid };
	Connection(std::shared_ptr<Room> inRoom1
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