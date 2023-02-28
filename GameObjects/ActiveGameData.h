#ifndef ACTIVE_GAME_DATA_H
#define ACTIVE_GAME_DATA_H
#include<memory>
#include "Game.h"


struct ActiveGameData
{	
	ActiveGameData(
	std::shared_ptr <Player>,
	std::shared_ptr <Character>,
	std::shared_ptr <Room>,
	std::shared_ptr <World>,
	std::shared_ptr <OutputManager>,
	Game::GameState);

	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Character> mAdversary;
	std::shared_ptr<Room> mRoom;
	std::shared_ptr<World> mWorld;
	std::shared_ptr<OutputManager> mOutputManager;
	Game::GameState mState;

};



#endif