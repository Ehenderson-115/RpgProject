#ifndef ROOM_H
#define ROOM_H
#include "Entity.h"
#include<string>
#include<vector>
#include<memory>

class Item;
class Character;

class Room : public Entity
{
public:
	enum class Direction {North, South, East, West, Invalid};
	Room();

	std::shared_ptr<Room> North() const;
	std::shared_ptr<Room> South() const;
	std::shared_ptr<Room> East() const;
	std::shared_ptr<Room> West() const;

	void North(std::shared_ptr<Room> inRoom);
	void South(std::shared_ptr<Room> inRoom);
	void East(std::shared_ptr<Room> inRoom);
	void West(std::shared_ptr<Room> inRoom);

	std::shared_ptr<Room> Room::ConnectedRoom(const Direction& inDir) const;
	std::shared_ptr<Room> Room::ConnectedRoom(const std::string& inStr);

	void AddRoomObject(std::shared_ptr<Entity> inEntity);

	void RoomId(int roomId, Direction inDir);
	void RoomId(int roomId, const std::string& inStr);

	int RoomId(const std::string& inStr);
	int RoomId(const Direction& inDir) const;

	std::string CheckRoomContents();

	std::shared_ptr<Item>GetItem(std::string nameToFind);
	std::shared_ptr<Character>GetCharacter(std::string nameToFind) const;
	void RemoveContent(std::string nameToFind);

private:

	std::vector<std::shared_ptr<Entity>> mContents;
	std::string mDescript;

	Direction TranslateDirection(const std::string inStr);

	int mNorthId;
	int mSouthId;
	int mEastId;
	int mWestId;

	std::shared_ptr<Room> mNorth;
	std::shared_ptr<Room> mSouth;
	std::shared_ptr<Room> mEast;
	std::shared_ptr<Room> mWest;


};

#endif 
