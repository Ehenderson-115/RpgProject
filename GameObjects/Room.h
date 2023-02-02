#ifndef ROOM_H
#define ROOM_H
#include "Entity.h"
#include<iostream>
#include<string>
#include<vector>
#include<memory>



class Character;


class Room : public Entity
{
public:
	
	void AddCharacter(std::shared_ptr<Character> inCharacter);
	void AddRoomObject(std::shared_ptr<Entity> inEntity);
	void AddRoomConnection(std::shared_ptr<Room> inRoom, char direction);
	void CheckRoomContents();
	void CheckRoomCharacters();


	std::shared_ptr<Room> GetRoom(char direction);
	
private:

	std::vector<std::shared_ptr<Entity>> mContents;
	std::string mDescript;

	std::shared_ptr<Room> mNorth;
	std::shared_ptr<Room> mSouth;
	std::shared_ptr<Room> mEast;
	std::shared_ptr<Room> mWest;
};

#endif 
