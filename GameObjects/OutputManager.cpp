#include "OutputManager.h"
#include "HelperFunctions.h"
#include "Character.h"
#include "Player.h"
#include "Room.h"
#include "ActiveGameData.h"

OutputManager::OutputManager()
	: mOutput{""}
	, mStatusBar{""}
{}

void OutputManager::UpdateStatusBar(const std::shared_ptr<ActiveGameData>& inData)
{
	switch (inData->State())
	{
	case Game::GameState::Main:
		mStatusBar = ("Current Location: " + inData->mRoom->Name() + "\n");
		break;
	case Game::GameState::Menu:
		mStatusBar = (inData->mPlayer->GetStatus() + "\n");
		break;
	case Game::GameState::Combat:
		mStatusBar = (inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus() + "\n");
		break;
	case Game::GameState::CombatStart:
		mStatusBar = (inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus() + "\n");
		break;
	case Game::GameState::CombatEndMain:
		mStatusBar = (inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus() + "\n");
		break;
	case Game::GameState::CombatEndClose:
		mStatusBar = (inData->mPlayer->Character::GetStatus() + " ||| " + inData->mAdversary->GetStatus() + "\n");
		break;
	}
}

void OutputManager::AddToOutput(const std::string& inStr)
{
	mOutput += inStr;
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
