#include "PlayerLocation.h"

PlayerLocation::PlayerLocation(std::shared_ptr<Player> inPlayer, std::shared_ptr<Room> inRoom)
	: mPlayer{inPlayer}
	, mRoom{inRoom}
{}