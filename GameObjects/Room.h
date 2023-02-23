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

	//Getters
	int RoomId(const Direction& inDir) const;
	int RoomId(const std::string& inStr) { return RoomId(TranslateDirection(inStr)); }
	std::shared_ptr<Room> North() const { return mNorth; }
	std::shared_ptr<Room> South() const { return mSouth; }
	std::shared_ptr<Room> East() const { return mEast; }
	std::shared_ptr<Room> West() const { return mWest; }
	std::shared_ptr<Item>GetItem(std::string nameToFind);
	std::shared_ptr<Character>GetCharacter(std::string nameToFind) const;
	std::shared_ptr<Room> Room::ConnectedRoom(const Direction& inDir) const;
	std::shared_ptr<Room> Room::ConnectedRoom(const std::string& inStr) { return ConnectedRoom(TranslateDirection(inStr)); }


	//Setters
	void North(std::shared_ptr<Room> inRoom) { mNorth = inRoom; }
	void South(std::shared_ptr<Room> inRoom) { mSouth = inRoom; }
	void East(std::shared_ptr<Room> inRoom) { mEast = inRoom; }
	void West(std::shared_ptr<Room> inRoom) { mWest = inRoom; }
	void AddRoomObject(std::shared_ptr<Entity> inEntity) { mContents.push_back(inEntity); }
	void RoomId(int roomId, Direction inDir);
	void RoomId(int roomId, const std::string& inStr) { RoomId(roomId, TranslateDirection(inStr)); }

	std::string CheckRoomContents();
	
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
