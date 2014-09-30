#include "abstractGame.h"

AbstractGame::AbstractGame(GameController* controller)
	: QObject(controller)
	, m_controller(controller)
{
}

AbstractGame::~AbstractGame()
{
	// Nothing to do here
}
