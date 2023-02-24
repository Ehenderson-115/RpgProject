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
	Room();

	//Content Functions
	std::shared_ptr<Item>GetItem(std::string nameToFind);
	std::shared_ptr<Character>GetCharacter(std::string nameToFind) const;
	std::string CheckRoomContents();
	
	void AddRoomObject(std::shared_ptr<Entity> inEntity) { mContents.push_back(inEntity); }
	void RemoveContent(std::string nameToFind);
	
	

private:

	std::vector<std::shared_ptr<Entity>> mContents;

};

#endif 
