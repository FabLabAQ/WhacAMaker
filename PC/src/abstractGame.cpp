#include "abstractGame.h"
#include "gameController.h"

AbstractGame::AbstractGame(GameController* controller)
	: QObject(controller)
	, m_controller(controller)
	, m_gameRunning(false)
{
}

AbstractGame::~AbstractGame()
{
	// Nothing to do here
}

bool AbstractGame::gameRunning() const
{
	return m_gameRunning;
}
