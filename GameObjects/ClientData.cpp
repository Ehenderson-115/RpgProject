#include "ClientData.h"
#include "OutputManager.h"

ClientData::ClientData(
	std::shared_ptr<Player> inPlayer,
	std::shared_ptr<Character> inAdversary,
	std::shared_ptr<Room> inRoom,
	std::shared_ptr<World> inWorld,
	std::shared_ptr<OutputManager> inOutputManager,
	GameState inState)
	: mPlayer {inPlayer}
	, mAdversary {inAdversary}
	, mRoom {inRoom}
	, mWorld {inWorld}
	, mOutputManager {inOutputManager}
	, mState {inState}
{}

void ClientData::State(GameState inState)
{
	mState = inState;
	mOutputManager->UpdateStatusBar(std::make_shared<ClientData>(*this));
}

ClientData::GameState ClientData::State()
{
	return mState;
}