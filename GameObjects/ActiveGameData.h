#ifndef ACTIVE_GAME_DATA_H
#define ACTIVE_GAME_DATA_H
#include<memory>
#include "Game.h"
class Player;
class Character;
class Room;
class World;
class OutputManager;

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

	void State(Game::GameState inState);
	Game::GameState State();
private:
	Game::GameState mState;

};



#endif