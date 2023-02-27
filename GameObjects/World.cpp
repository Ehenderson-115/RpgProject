#include "World.h"
#include "Connection.h"
#include "PlayerLocation.h"
#include "Room.h"
#include "Player.h"

std::shared_ptr<Room> World::GetConnectedRoom(std::shared_ptr<Room> inRoom, Connection::Direction inDirection)
{
	for (auto connection : mRoomConnections)
	{
		if (connection->mMainRoom == inRoom && inDirection == connection->mConnectionDir)
		{
			return connection->mConnectedRoom;
		}
	}
	return nullptr;
}

std::shared_ptr<Room> World::GetPlayerLoc(std::shared_ptr<Player> inPlayer)
{
	for (auto location : mPlayerLocs)
	{
		if (inPlayer == location->mPlayer)
		{
			return location->mRoom;
		}
	}
	return nullptr;
}

void World::AddRoomConnection(std::shared_ptr<Room> inMainRoom, std::shared_ptr<Room> inConnectedRoom, Connection::Direction inConnectionDir)
{
	//Room connected to nullptr is possible due to possible omission of connected room to the first room in the config file.
	//Also removing an existing room connection before adding one allows for room layout to be adjusted at runtime.
	RemoveRoomConnection(inMainRoom, inConnectionDir);

	mRoomConnections.push_back(std::make_shared<Connection>(inMainRoom, inConnectedRoom, inConnectionDir));
	mRoomConnections.push_back(std::make_shared<Connection>(inConnectedRoom, inMainRoom, Connection::GetOpposite(inConnectionDir)));
}

void World::AddPlayerLocation(std::shared_ptr<Player> inPlayer, std::shared_ptr<Room> inRoom)
{
	RemovePlayerLocation(inPlayer);
	mPlayerLocs.push_back(std::make_shared<PlayerLocation>(inPlayer, inRoom));
}

void World::RemoveRoomConnection(std::shared_ptr<Room> inRoom, Connection::Direction inConnectionDir)
{
	for (int i = 0; i < mRoomConnections.size(); i++)
	{
		auto connection = mRoomConnections.at(i);
		if (connection->mMainRoom == inRoom && connection->mConnectionDir == inConnectionDir)
		{
			mRoomConnections.erase(mRoomConnections.begin() + i);
			RemoveRoomConnection(connection->mConnectedRoom, Connection::GetOpposite(inConnectionDir));
		}
	}
}

void World::RemovePlayerLocation(std::shared_ptr<Player> inPlayer)
{
	for (int i = 0; i < mPlayerLocs.size(); i++)
	{
		auto playerLoc = mPlayerLocs.at(i);
		if (playerLoc->mPlayer == inPlayer)
		{
			mPlayerLocs.erase(mPlayerLocs.begin() + i);
		}
	}
}