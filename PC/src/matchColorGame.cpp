#include "matchColorGame.h"
#include "gameController.h"

MatchColorGame::MatchColorGame(GameController* controller)
	: AbstractGame(controller)
{
#warning TODO!!!
}

MatchColorGame::~MatchColorGame()
{
#warning TODO!!!
}

void MatchColorGame::startGame(WhacAMaker::DifficultyLevel difficulty)
{
#warning TODO!!!
}

void MatchColorGame::stopGame()
{
#warning TODO!!!
	// Ending game with no highscore
	m_controller->stopGame(false);
}

void MatchColorGame::pointerStatus(int moleID, bool button1Pressed, bool button2Pressed)
{
#warning TODO!!!
}

qreal MatchColorGame::score() const
{
#warning TODO!!!

	return 0.0;
}

