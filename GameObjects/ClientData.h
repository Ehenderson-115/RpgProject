#ifndef CLIENT_DATA_H
#define CLIENT_DATA_H
#include <memory>
#include <mutex>
class Player;
class Character;
class Room;
class World;
class OutputManager;

struct ClientData
{	
	enum class GameState { Error, Menu, Combat, CombatStart, CombatEndMain, CombatEndClose, Main, Closing };
	ClientData(
	std::shared_ptr <Player>,
	std::shared_ptr <Character>,
	std::shared_ptr <Room>,
	std::shared_ptr <World>,
	std::shared_ptr <OutputManager>,
	std::shared_ptr <std::mutex>,
	GameState);

	
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Character> mAdversary;
	std::shared_ptr<Room> mRoom;
	std::shared_ptr<World> mWorld;
	std::shared_ptr<std::mutex> mMutex;
	std::shared_ptr<OutputManager> mOutputManager;

	void State(GameState inState);
	GameState State();
private:
	GameState mState;

};



#endif