#ifndef ROOM_H
#define ROOM_H
#include "Entity.h"
#include<string>
#include<vector>
#include<memory>

class Item;

class Room : public Entity
{
public:
	enum class Direction {North, South, East, West, Invalid};
	Room();
	void AddRoomObject(std::shared_ptr<Entity> inEntity);

	void RoomConnection(int roomId, Direction inDir);
	void RoomConnection(int roomId, const std::string& inStr);

	int RoomConnection(const std::string& inStr);
	int RoomConnection(Direction inDir) const;

	std::string CheckRoomContents();
	std::shared_ptr<Item>GetItem(std::string nameToFind);

private:

	std::vector<std::shared_ptr<Entity>> mContents;
	std::string mDescript;

	Direction TranslateDirection(const std::string inStr);

	int mNorthId;
	int mSouthId;
	int mEastId;
	int mWestId;
};

#endif 
