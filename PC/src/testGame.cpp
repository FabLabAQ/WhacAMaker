#include "testGame.h"
#include "gameController.h"

TestGame::TestGame(GameController* controller)
	: AbstractGame(controller)
{
#warning TODO!!!
}

TestGame::~TestGame()
{
#warning TODO!!!
}

void TestGame::startGame(WhacAMaker::DifficultyLevel difficulty)
{
#warning TODO!!!
}

void TestGame::stopGame()
{
#warning TODO!!!
	// Ending game with no highscore
	m_controller->stopGame(false);
}

void TestGame::pointerStatus(int moleID, bool button1Pressed, bool button2Pressed)
{
#warning TODO!!!
}

qreal TestGame::score() const
{
	return 0.0;
}

