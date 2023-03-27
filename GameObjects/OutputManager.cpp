#include "OutputManager.h"
#include "HelperFunctions.h"
#include "Character.h"
#include "Player.h"
#include "Room.h"
#include "ClientData.h"

OutputManager::OutputManager()
	: mOutput{""}
	, mStatusBar{""}
{}

void OutputManager::UpdateStatusBar(const std::shared_ptr<ClientData>& inData)
{
	switch (inData->State())
	{
	case ClientData::GameState::Main:
		mStatusBar = ("Current Location: " + inData->mRoom->Name() + "\n");
		break;
	case ClientData::GameState::Menu:
		mStatusBar = (inData->mPlayer->GetStatus() + "\n");
		break;
	case ClientData::GameState::Combat:
		mStatusBar = (inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus() + "\n");
		break;
	case ClientData::GameState::CombatStart:
		mStatusBar = (inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus() + "\n");
		break;
	case ClientData::GameState::CombatEndMain:
		mStatusBar = (inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus() + "\n");
		break;
	case ClientData::GameState::CombatEndClose:
		mStatusBar = (inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus() + "\n");
		break;
	}
}


void OutputManager::PrintScreen()
{
	system("cls");
	FormattedPrint(mStatusBar);
	if (!mOutput.empty())
	{
		FormattedPrint(mOutput);
	}
	mOutput.clear();
}

