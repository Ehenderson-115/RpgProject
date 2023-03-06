#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <memory>
#include "Entity.h"
#include "RoomConnection.h"

struct PlayerLocation;
class Player;
class Room;

class World : public Entity
{
public:
	//Getters
	std::shared_ptr<Room> GetConnectedRoom(std::shared_ptr<Room> inRoom, RoomConnection::Direction inDirection);
	std::shared_ptr<Room> GetPlayerLoc(std::shared_ptr<Player> inPlayer);

	//Setters
	void AddRoomConnection(std::shared_ptr<Room> inMainRoom, std::shared_ptr<Room> inConnectedRoom, RoomConnection::Direction inConnectionDir);
	void AddPlayerLocation(std::shared_ptr<Player> inPlayer, std::shared_ptr<Room> inRoom);

	void RemoveRoomConnection(std::shared_ptr<Room> inRoom, RoomConnection::Direction inConnectionDir);
	void RemovePlayerLocation(std::shared_ptr<Player> inPlayer);


private:
	std::vector<std::shared_ptr<RoomConnection>> mRoomConnections;
	std::vector <std::shared_ptr<PlayerLocation>> mPlayerLocs;

};
#endif
