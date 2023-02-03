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
	void AddRoomConnection(int input, char direction);
	void CheckRoomContents();
	void CheckRoomCharacters();


	std::shared_ptr<Room> GetRoom(char direction);
	
private:

	std::vector<std::shared_ptr<Entity>> mContents;
	std::string mDescript;

	int mNorthId;
	int mSouthId;
	int mEastId;
	int mWestId;
};

#endif 
