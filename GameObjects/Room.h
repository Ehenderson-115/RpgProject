#ifndef ROOM_H
#define ROOM_H
#include "Entity.h"
#include "Item.h"
#include "HelperFunctions.h"
#include<iostream>
#include<string>
#include<vector>
#include<memory>



class Character;


class Room : public Entity
{
public:
	void AddRoomObject(std::shared_ptr<Entity> inEntity);
	void AddRoomConnection(int input, char direction);
	std::string CheckRoomContents();
	std::shared_ptr<Item>GetItem(std::string nameToFind);


	int GetRoom(std::string inStr);
	
private:

	std::vector<std::shared_ptr<Entity>> mContents;
	std::string mDescript;

	char TranslateDirection(const std::string inStr);

	int mNorthId;
	int mSouthId;
	int mEastId;
	int mWestId;
};

#endif 
