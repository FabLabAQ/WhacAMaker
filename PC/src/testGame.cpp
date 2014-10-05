#include "testGame.h"
#include "gameController.h"

TestGame::TestGame(GameController* controller)
	: AbstractGame(controller)
	, m_molesStatus(0)
{
}

TestGame::~TestGame()
{
	// Nothing to do here
}

void TestGame::startGame(WhacAMaker::DifficultyLevel difficulty)
{
	// Bringing all moles down
	m_molesStatus = 0;
	m_controller->updateArduinoMolesStatus(m_molesStatus);
}

void TestGame::stopGame()
{
	// Ending game with no highscore
	m_controller->stopGame(false);
}

void TestGame::pointerStatus(int moleID, bool button1Pressed, bool button2Pressed)
{
	if (!m_gameStarted) {
		return;
	}

	// Moving moles depending on joystick commands. If both buttons are pressed stopping test
	if (button1Pressed && button2Pressed) {
		stopGame();
	} else if (button1Pressed) {
		m_molesStatus |= (1 << moleID);
		m_controller->updateArduinoMolesStatus(m_molesStatus);
	} else if (button2Pressed) {
		m_molesStatus &= ~(1 << moleID);
		m_controller->updateArduinoMolesStatus(m_molesStatus);
	}
}

qreal TestGame::score() const
{
	return 0.0;
}

