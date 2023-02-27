#ifndef PLAYERLOCATION_H
#define PLAYERLOCATION_H

#include <memory>

class Player;
class Room;

struct PlayerLocation
{
	PlayerLocation(std::shared_ptr<Player> inPlayer, std::shared_ptr<Room> inRoom);

	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Room> mRoom;

};




#endif // !PLAYERLOCATION_H

