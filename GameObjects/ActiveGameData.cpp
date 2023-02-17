#include "ActiveGameData.h"

ActiveGameData::ActiveGameData(
	std::shared_ptr<Player> inPlayer,
	std::shared_ptr<Character> inAdversary,
	std::shared_ptr<Room> inRoom,
	Game::GameState inState)
	: mPlayer {inPlayer}
	, mAdversary {inAdversary}
	, mRoom {inRoom}
	, mState {inState}
{};