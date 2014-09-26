#include "gameController.h"
#include "myRuntimeException.h"
#include "controller.h"
#include "joystickPointer.h"
#include "helpers.h"
#include <QQmlProperty>

// Useful constants
namespace {
	/**
	 * \brief How many seconds the game lasts
	 */
	const int gameDuration = 120;
}

GameController::GameController(Controller* controller, JoystickPointer* pointer, QQuickView& view, QObject* parent)
	: QObject(parent)
	, m_controller(controller)
	, m_pointer(pointer)
	, m_qmlGamePanel(getQmlObject(view, "gamePanelObject"))
	, m_remainingSeconds(0)
	, m_timer()
	, m_difficultyLevel(WhackAMaker::Easy)
{
	// Connecting the joystick absolute movement signal from the joystick pointer to our slot
	connect(m_pointer, SIGNAL(joystickMovedAbsolute(qreal, qreal, bool, bool)), this, SLOT(pointerPosition(qreal, qreal, bool, bool)));

	// Connecting timer signal
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));

	// Connecting to QML signals
	connect(m_qmlGamePanel, SIGNAL(terminateGame()), this, SLOT(terminateGame()));
}

GameController::~GameController()
{
	// Nothing to do here
}

void GameController::startGame()
{
	// Changing the pointer and the movement type
	m_pointer->setStatus(JoystickPointer::Game);
	m_pointer->setMovementType(JoystickPointer::Absolute);
	const qreal gameAreaSize = QQmlProperty::read(m_qmlGamePanel, "gameAreaSize").toReal();
	m_pointer->setMovementArea(QRectF(0.0, 0.0, gameAreaSize, gameAreaSize));

	// Getting the difficulty level
	m_difficultyLevel = static_cast<WhackAMaker::DifficultyLevel>(QQmlProperty::read(m_qmlGamePanel, "difficultyLevel").toInt());

	// Actually start game
	m_remainingSeconds = gameDuration;
	// This is not very accurate (each timeout signal has 5% tolerance), but for he moment it is enough
	m_timer.start(1000);

	// Setting initial value of information
	QQmlProperty::write(m_qmlGamePanel, "infoLevel", WhackAMaker::difficultyLevelToString(m_difficultyLevel));
	QQmlProperty::write(m_qmlGamePanel, "infoScore", "0");
	QQmlProperty::write(m_qmlGamePanel, "infoAmmo", "100");
	QQmlProperty::write(m_qmlGamePanel, "infoTime", remainingTimeString());
}

void GameController::pointerPosition(qreal x, qreal y, bool button1Pressed, bool button2Pressed)
{
// 	qui bisogna riscalare x e y perché sono nel frame dell intera finestra, invece ci serve solo nell area di gioco
//
// 	inoltre il puntatore del gioco disegnarlo come un martello. quando si fa click, se c è la talpa appare il colpo (forse stella), se non è colpito solo il martello abbassato
}

void GameController::terminateGame()
{
	// Ending game with no highscore
	const QVariant newHighScore(false);
	QMetaObject::invokeMethod(m_qmlGamePanel, "endGame", Q_ARG(QVariant, newHighScore));
}

void GameController::timeout()
{
	m_remainingSeconds--;

	// Updating qml property
	QQmlProperty::write(m_qmlGamePanel, "infoTime", remainingTimeString());

	// Checking if game has ended
	if (m_remainingSeconds == 0) {
		m_timer.stop();

		const QVariant newHighScore = m_controller->newHighScore(m_difficultyLevel, 10.0);
		QMetaObject::invokeMethod(m_qmlGamePanel, "endGame", Q_ARG(QVariant, newHighScore));
	}
}

QString GameController::remainingTimeString() const
{
	return QString("%1:%2").arg(m_remainingSeconds / 60).arg(m_remainingSeconds % 60, 2, 10, QChar('0'));
}
