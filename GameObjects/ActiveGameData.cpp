#include "ActiveGameData.h"

ActiveGameData::ActiveGameData(
	std::shared_ptr<Player> inPlayer,
	std::shared_ptr<Character> inAdversary,
	std::shared_ptr<Room> inRoom,
	std::shared_ptr<World> inWorld,
	Game::GameState inState)
	: mPlayer {inPlayer}
	, mAdversary {inAdversary}
	, mRoom {inRoom}
	, mWorld {inWorld}
	, mState {inState}
{};