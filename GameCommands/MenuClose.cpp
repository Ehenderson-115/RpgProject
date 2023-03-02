#include "MenuClose.h"

MenuClose::MenuClose(std::shared_ptr<ActiveGameData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuClose::Execute()
{
	mGameData->State(Game::GameState::Main);
}