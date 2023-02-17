#ifndef ACTIVE_GAME_DATA_H
#define ACTIVE_GAME_DATA_H
#include<memory>
#include "Game.h"


struct ActiveGameData
{	
	ActiveGameData(
	std::shared_ptr <Player>,
	std::shared_ptr<Character>,
	std::shared_ptr<Room>,
	Game::GameState);

	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Character> mAdversary;
	std::shared_ptr<Room> mRoom;
	Game::GameState mState;

};



#endif