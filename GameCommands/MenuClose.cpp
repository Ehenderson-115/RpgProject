#include "MenuClose.h"

MenuClose::MenuClose(std::shared_ptr<ClientData> inData, std::string inArgs)
	: GameCommand(inData, inArgs)
{};

void MenuClose::Execute()
{
	mGameData->State(ClientData::GameState::Main);
}