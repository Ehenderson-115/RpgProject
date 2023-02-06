#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "Character.h"
#include "Room.h"


class Item;

class Player : public Character
{
public:
	void SetCurrRoomId(int inRoomId);
	int GetCurrRoom();
	
private:
	int currRoomId;
	std::vector<std::shared_ptr<Entity>> inventory;
	
};
#endif