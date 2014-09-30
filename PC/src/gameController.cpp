#include "gameController.h"
#include "myRuntimeException.h"
#include "controller.h"
#include "joystickPointer.h"
#include "helpers.h"
#include "classicalGame.h"
#include "matchColorGame.h"
#include "testGame.h"
#include <QQmlProperty>
#include <QDateTime>
#include <cstdlib>
#include <algorithm>

GameController::GameController(Controller* controller, JoystickPointer* pointer, SerialCommunication* serialCommunication, QQuickView& view, QObject* parent)
	: QObject(parent)
	, m_controller(controller)
	, m_pointer(pointer)
	, m_serialCommunication(serialCommunication)
	, m_qmlGamePanel(getQmlObject(view, "gamePanelObject"))
	, m_game(NULL)
	, m_gameType(WhacAMaker::Classical)
	, m_difficultyLevel(WhacAMaker::Easy)
	, m_gameAreaSize(0)
{
	// Connecting the joystick absolute movement signal from the joystick pointer to our slot
	connect(m_pointer, SIGNAL(joystickMovedAbsolute(qreal, qreal, bool, bool)), this, SLOT(pointerPosition(qreal, qreal, bool, bool)));

	// Connecting to QML signals
	connect(m_qmlGamePanel, SIGNAL(terminateGame()), this, SLOT(terminateGame()));
}

GameController::~GameController()
{
	delete m_game;
}

void GameController::startGame()
{
	// Bringing all moles down
	updateArduinoMolesStatus(0);

	// Changing the pointer and the movement type
	m_pointer->setStatus(JoystickPointer::Game);
	m_pointer->setMovementType(JoystickPointer::Absolute);
	m_gameAreaSize = QQmlProperty::read(m_qmlGamePanel, "gameAreaSize").toReal();
	m_pointer->setMovementArea(QRectF(m_gameAreaSize / 6.0, m_gameAreaSize / 6.0, 2.0 * m_gameAreaSize / 3.0, 2.0 * m_gameAreaSize / 3.0));

	// Getting the difficulty level and game type
	m_gameType = static_cast<WhacAMaker::GameType>(QQmlProperty::read(m_qmlGamePanel, "gameModality").toInt());
	m_difficultyLevel = static_cast<WhacAMaker::DifficultyLevel>(QQmlProperty::read(m_qmlGamePanel, "difficultyLevel").toInt());

	// Creating the game object, depending on the value of m_gameType
	gameFactory();

	// Starting the game
	m_game->startGame(m_difficultyLevel);
}

void GameController::stopGame(bool checkHighScore)
{
	// Bringing all moles down
	updateArduinoMolesStatus(0);

	QVariant newHighScore;
	if (checkHighScore) {
		newHighScore = m_controller->newHighScore(m_difficultyLevel, m_game->score());
	} else {
		newHighScore = false;
	}
	QMetaObject::invokeMethod(m_qmlGamePanel, "endGame", Q_ARG(QVariant, newHighScore));
}

void GameController::updateArduinoMolesStatus(int status)
{
	// Sending command to Arduino
	m_serialCommunication->newCommandToSend();
	m_serialCommunication->appendCommandPart("M");
	m_serialCommunication->appendCommandPart(status);
	m_serialCommunication->sendCommand();
}

void GameController::pointerPosition(qreal x, qreal y, bool button1Pressed, bool button2Pressed)
{
	// Checking which mole is under the pointer
	int moleX = 1;
	if (x < (m_gameAreaSize / 3.0)) {
		moleX = 0;
	} else if (x > (2.0 * m_gameAreaSize / 3.0)) {
		moleX = 2;
	}
	int moleY = 1;
	if (y < (m_gameAreaSize / 3.0)) {
		moleY = 0;
	} else if (y > (2.0 * m_gameAreaSize / 3.0)) {
		moleY = 2;
	}
	const int moleID = moleX + moleY * 3;

	// Updating the pointed mole
	QMetaObject::invokeMethod(m_qmlGamePanel, "setPointedMole", Q_ARG(QVariant, QVariant(moleID)));

	// Calling game-specific function
	m_game->pointerStatus(moleID, button1Pressed, button2Pressed);
}

void GameController::terminateGame()
{
	// Telling game to stop
	m_game->stopGame();
}

void GameController::gameFactory()
{
	delete m_game;

	switch(m_gameType) {
		case WhacAMaker::Test:
			m_game = new TestGame(this);
			break;
		case WhacAMaker::Classical:
			m_game = new ClassicalGame(this);
			break;
		case WhacAMaker::MatchColor:
			m_game = new MatchColorGame(this);
			break;
	}
}
