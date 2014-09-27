#include "gameController.h"
#include "myRuntimeException.h"
#include "controller.h"
#include "joystickPointer.h"
#include "helpers.h"
#include <QQmlProperty>
#include <QDateTime>
#include <cstdlib>

// Useful constants
namespace {
	// How many seconds the game lasts
	const int gameDuration = 120;
	// The interval between moles changes in various difficulty levels in milliseconds
	const int easyInterval = 1000;
	const int mediumInterval = 800;
	const int hardInterval = 500;
	const int testInterval = 2000;
	// The initial number of hits in various difficulty levels
	const int easyAmmo = 100;
	const int mediumAmmo = 80;
	const int hardAmmo = 50;
}

GameController::GameController(Controller* controller, JoystickPointer* pointer, SerialCommunication* serialCommunication, QQuickView& view, QObject* parent)
	: QObject(parent)
	, m_controller(controller)
	, m_pointer(pointer)
	, m_serialCommunication(serialCommunication)
	, m_qmlGamePanel(getQmlObject(view, "gamePanelObject"))
	, m_remainingSeconds(0)
	, m_timer()
	, m_difficultyLevel(WhackAMaker::Easy)
	, m_molesStatus(0)
	, m_gameTimer()
	, m_score(0)
	, m_ammoLeft(0)
	, m_gameAreaSize(0)
	, m_prevButtonPressed(false)
{
	// Connecting the joystick absolute movement signal from the joystick pointer to our slot
	connect(m_pointer, SIGNAL(joystickMovedAbsolute(qreal, qreal, bool, bool)), this, SLOT(pointerPosition(qreal, qreal, bool, bool)));

	// Connecting timer signals
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
	connect(&m_gameTimer, SIGNAL(timeout()), this, SLOT(changeMolesStatus()));

	// Connecting to QML signals
	connect(m_qmlGamePanel, SIGNAL(terminateGame()), this, SLOT(terminateGame()));

	// We also need to initialize the random number generator
	qsrand(uint(QDateTime::currentMSecsSinceEpoch() / 1000));
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
	m_gameAreaSize = QQmlProperty::read(m_qmlGamePanel, "gameAreaSize").toReal();
	m_pointer->setMovementArea(QRectF(m_gameAreaSize / 6.0, m_gameAreaSize / 6.0, 2.0 * m_gameAreaSize / 3.0, 2.0 * m_gameAreaSize / 3.0));

	// Getting the difficulty level
	m_difficultyLevel = static_cast<WhackAMaker::DifficultyLevel>(QQmlProperty::read(m_qmlGamePanel, "difficultyLevel").toInt());

	// Actually start game
	m_remainingSeconds = gameDuration;
	// This is not very accurate (each timeout signal has 5% tolerance), but for he moment it is enough
	m_timer.start(1000);

	// Setting initial value of information
	QQmlProperty::write(m_qmlGamePanel, "infoLevel", WhackAMaker::difficultyLevelToString(m_difficultyLevel));
	QQmlProperty::write(m_qmlGamePanel, "infoTime", remainingTimeString());
	m_score = 0;
	if (m_difficultyLevel == WhackAMaker::Easy) {
		m_ammoLeft = easyAmmo;
	} else if (m_difficultyLevel == WhackAMaker::Medium) {
		m_ammoLeft = mediumAmmo;
	} else if (m_difficultyLevel == WhackAMaker::Hard) {
		m_ammoLeft = hardAmmo;
	} else {
		m_ammoLeft = 11;
	}
	updateScoreAndAmmoGUI();

	// Starting the timer for the game. The speed depends on the difficulty level
	int msec = 100000;
	if (m_difficultyLevel == WhackAMaker::Easy) {
		msec = easyInterval;
	} else if (m_difficultyLevel == WhackAMaker::Medium) {
		msec = mediumInterval;
	} else if (m_difficultyLevel == WhackAMaker::Hard) {
		msec = hardInterval;
	} else {
		msec = testInterval;
	}
	m_gameTimer.start(msec);
}

void GameController::pointerPosition(qreal x, qreal y, bool button1Pressed, bool button2Pressed)
{
	// In test we don't consider the joystick
	if (m_difficultyLevel == WhackAMaker::Test) {
		return;
	}

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

	const bool buttonPressed = button1Pressed || button2Pressed;
	if (m_prevButtonPressed && !buttonPressed && (m_ammoLeft != 0)) {
		// An hit attempt!
		m_ammoLeft--;

		// Checking if a mole was hit
		if (((m_molesStatus >> moleID) & 1) == 1) {
			// Good shot, mole hit!
			m_score++;

			// Bringing the mole down and updating moles status
			m_molesStatus &= ~(1 << moleID);
			updateMolesStatus();
		}

		updateScoreAndAmmoGUI();
	}

	m_prevButtonPressed = buttonPressed;
}

void GameController::terminateGame()
{
	// Ending game with no highscore
	stopGame();
	const QVariant newHighScore(false);
	QMetaObject::invokeMethod(m_qmlGamePanel, "endGame", Q_ARG(QVariant, newHighScore));
}

void GameController::timeout()
{
	m_remainingSeconds--;

	// Updating qml property
	QQmlProperty::write(m_qmlGamePanel, "infoTime", remainingTimeString());

	// Checking if game has ended
	if ((m_remainingSeconds == 0) || (m_ammoLeft == 0)) {
		stopGame();

		QVariant newHighScore;
		if (m_difficultyLevel == WhackAMaker::Test) {
			newHighScore = false;
		} else {
			newHighScore = m_controller->newHighScore(m_difficultyLevel, m_score);
		}
		QMetaObject::invokeMethod(m_qmlGamePanel, "endGame", Q_ARG(QVariant, newHighScore));
	}
}

void GameController::changeMolesStatus()
{
	if (m_difficultyLevel == WhackAMaker::Test) {
		// Activating the moles in sequence
		if (m_ammoLeft == 11) {
			m_molesStatus = 256;
		} else {
			m_molesStatus >>= 1;
		}

		m_ammoLeft--;

		updateScoreAndAmmoGUI();
	} else {
#warning IL NUMERO DI TALPE DOVREBBE DIPENDERE DAL LIVELLO DI DIFFICOLTÀ
		m_molesStatus = qrand();
	}

	updateMolesStatus();
}

QString GameController::remainingTimeString() const
{
	return QString("%1:%2").arg(m_remainingSeconds / 60).arg(m_remainingSeconds % 60, 2, 10, QChar('0'));
}

void GameController::updateMolesStatus()
{
	// Sending command to Arduino
	m_serialCommunication->newCommandToSend();
	m_serialCommunication->appendCommandPart("M");
	m_serialCommunication->appendCommandPart(m_molesStatus);
	m_serialCommunication->sendCommand();

	// Updating qml game panel
	QMetaObject::invokeMethod(m_qmlGamePanel, "changeMoleSpotStatus", Q_ARG(QVariant, QVariant(m_molesStatus)));
}

void GameController::stopGame()
{
	m_timer.stop();
	m_gameTimer.stop();
	m_molesStatus = 0;
	updateMolesStatus();
}

void GameController::updateScoreAndAmmoGUI()
{
	QQmlProperty::write(m_qmlGamePanel, "infoScore", QString::number(m_score));
	QQmlProperty::write(m_qmlGamePanel, "infoAmmo", QString::number(m_ammoLeft));
}

