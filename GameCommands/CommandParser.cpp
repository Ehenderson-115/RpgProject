#include "CommandParser.h"
#include "GameCommand.h"
#include "../GameObjects/ActiveGameData.h"
#include "../GameObjects/HelperFunctions.h"

#include "MainLook.h"
#include "MainMove.h"
#include "MainGrabItem.h"
#include "MainSearch.h"
#include "MainOpen.h"
#include "MainClose.h"
#include "MainStartCombat.h"

#include "MenuInspect.h"
#include "MenuEquip.h"
#include "MenuListItems.h"
#include "MenuClose.h"

std::shared_ptr<GameCommand> CommandParser::ParseCommandString(std::shared_ptr<ActiveGameData>& gameData, std::string& commandStr)
{
	switch (gameData->mState)
	{
	case(Game::GameState::Main):
		return GenerateMainCommand(gameData, commandStr);
	case(Game::GameState::Menu):
		return GenerateMenuCommand(gameData, commandStr);
	case(Game::GameState::Combat):
		return GenerateCombatCommand(gameData, commandStr);
	case(Game::GameState::CombatStart):
		return GenerateCombatCommand(gameData, commandStr);
	default:
		return nullptr;
	}
}

std::shared_ptr<GameCommand> CommandParser::GenerateMainCommand(std::shared_ptr<ActiveGameData>& gameData, std::string& commandStr)
{
	std::string topLevelCommand = GrabNextArg(commandStr);
	if (topLevelCommand == "look")
	{
		auto command = std::make_shared<MainLook>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "move" || topLevelCommand == "goto")
	{
		auto command = std::make_shared<MainMove>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "grab" || topLevelCommand == "pickup")
	{
		auto command = std::make_shared<MainGrabItem>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "search" || topLevelCommand == "survey")
	{
		auto command = std::make_shared<MainSearch>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "open" || topLevelCommand == "o")
	{
		auto command = std::make_shared<MainOpen>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "attack" || topLevelCommand == "engage")
	{
		auto command = std::make_shared<MainStartCombat>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "exit" || topLevelCommand == "close")
	{
		auto command = std::make_shared<MainClose>(gameData, commandStr);
		return command;
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<GameCommand> CommandParser::GenerateMenuCommand(std::shared_ptr<ActiveGameData>& gameData, std::string& commandStr)
{
	std::string topLevelCommand = GrabNextArg(commandStr);
	if (topLevelCommand == "look")
	{
		std::string nextArg = GrabNextArg(commandStr);
		if (nextArg != "at")
		{
			FormattedPrint("Invalid look argument: \"" + nextArg + "\". Did you mean \"at\"?");
			return nullptr;
		}
		auto command = std::make_shared<MenuInspect>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "inspect")
	{
		auto command = std::make_shared<MenuInspect>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "equip" || topLevelCommand == "e")
	{
		auto command = std::make_shared<MenuEquip>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "ls" || topLevelCommand == "list")
	{
		auto command = std::make_shared<MenuListItems>(gameData, commandStr);
		return command;
	}
	else if (topLevelCommand == "exit" || topLevelCommand == "close")
	{
		auto command = std::make_shared<MenuClose>(gameData, commandStr);
		return command;
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<GameCommand> CommandParser::GenerateCombatCommand(std::shared_ptr<ActiveGameData>& gameData, std::string& commandStr)
{
	return std::shared_ptr<GameCommand>();
}
