#include "ActiveGameData.h"
#include "OutputManager.h"

ActiveGameData::ActiveGameData(
	std::shared_ptr<Player> inPlayer,
	std::shared_ptr<Character> inAdversary,
	std::shared_ptr<Room> inRoom,
	std::shared_ptr<World> inWorld,
	std::shared_ptr<OutputManager> inOutputManager,
	Game::GameState inState)
	: mPlayer {inPlayer}
	, mAdversary {inAdversary}
	, mRoom {inRoom}
	, mWorld {inWorld}
	, mOutputManager {inOutputManager}
	, mState {inState}
{}

void ActiveGameData::State(Game::GameState inState)
{
	mState = inState;
	mOutputManager->UpdateStatusBar(std::make_shared<ActiveGameData>(*this));
}

Game::GameState ActiveGameData::State()
{
	return mState;
}