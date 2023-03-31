#include "ClientData.h"
#include "OutputManager.h"
#include "HelperFunctions.h"

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
	, mWorld{ inWorld }
	, mOutputManager {inOutputManager}
	, mState {inState}
{}

void ClientData::State(GameState inState)
{
	mState = inState;
	mOutputManager->UpdateStatusBar(std::make_shared<ClientData>(*this));
}

ClientData::GameState ClientData::State( )
{
	return mState;
}

ClientData::GameState ClientData::TranslateState(std::string inStr)
{
	inStr = StrToLower(inStr);
	if(inStr == "error")
	{
		return GameState::Error;
	}
	else if(inStr == "menu")
	{
		return GameState::Menu;
	}
	else if(inStr == "combat")
	{
		return GameState::Combat;
	}
	else if(inStr == "combatstart")
	{
		return GameState::CombatStart;
	}
	else if(inStr == "combatendmain")
	{
		return GameState::CombatEndMain;
	}
	else if(inStr == "combatendclose")
	{
		return GameState::CombatEndClose;
	}
	else if(inStr == "main")
	{
		return GameState::Main;
	}
	else if(inStr == "closing")
	{
		return GameState::Closing;
	}
	else
	{
		return GameState::Error;
	}
}

std::string ClientData::TranslateState(GameState inState)
{
	switch (inState)
	{
	case GameState::Menu:
		return "menu";
		break;		
	case GameState::Combat:
		return "combat";
		break;		
	case GameState::CombatStart:
		return "combatstart";
		break;		
	case GameState::CombatEndMain:
		return "combatendmain";
		break;		
	case GameState::CombatEndClose:
		return "combatendclose";
		break;		
	case GameState::Main:
		return "main";
		break;		
	case GameState::Closing:
		return "closing";
		break;
	case GameState::Error:
	default:
		return "error";
		break;
	}
}


std::string ClientData::GetStateString()
{
	return ("<" + TranslateState(mState) + ">");
}

std::string ClientData::GetStatusBar()
{
	return ("<" + mOutputManager->StatusBar() + ">");
}

std::string ClientData::GetOutput()
{
	return ("<" + mOutputManager->Output() +">");
}
