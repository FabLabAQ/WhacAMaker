#include "gameController.h"
#include "myRuntimeException.h"
#include "controller.h"
#include "joystickPointer.h"
#include "helpers.h"
#include <QQmlProperty>
#include <QDateTime>
#include <cstdlib>
#include <algorithm>

// Useful constants
namespace {
	// How many seconds the game lasts
	const int gameDuration = 120;
	// The interval between moles changes in various difficulty levels in milliseconds
	const int easyInterval = 5000;
	const int mediumInterval = 3000;
	const int hardInterval = 1000;
	const int testInterval = 20000;
	// The initial number of hits in various difficulty levels
	const int easyAmmo = 100;
	const int mediumAmmo = 80;
	const int hardAmmo = 50;
	const int testAmmo = 10000;
	// The number of moles at each step for various difficulty levels
	const int easyNumMoles = 6;
	const int mediumNumMoles = 4;
	const int hardNumMoles = 4;
}

GameController::GameController(Controller* controller, JoystickPointer* pointer, SerialCommunication* serialCommunication, QQuickView& view, QObject* parent)
	: QObject(parent)
	, m_controller(controller)
	, m_pointer(pointer)
	, m_serialCommunication(serialCommunication)
	, m_qmlGamePanel(getQmlObject(view, "gamePanelObject"))
	, m_remainingSeconds(0)
	, m_timer()
	, m_difficultyLevel(WhacAMaker::Easy)
	, m_molesStatus(0)
	, m_gameTimer()
	, m_score(0)
	, m_ammoLeft(0)
	, m_numMolesPerStep(easyNumMoles)
	, m_gameAreaSize(0)
	, m_prevButtonPressed(false)
	, m_moles(9)
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

	// Initializig the vector of moles ids
	for (int i = 0; i < m_moles.size(); ++i) {
		m_moles[i] = i;
	}
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
	m_difficultyLevel = static_cast<WhacAMaker::DifficultyLevel>(QQmlProperty::read(m_qmlGamePanel, "difficultyLevel").toInt());

	// Actually start game
	m_remainingSeconds = gameDuration;
	// This is not very accurate (each timeout signal has 5% tolerance), but for he moment it is enough
	m_timer.start(1000);

	// Setting initial value of information
	QQmlProperty::write(m_qmlGamePanel, "infoLevel", WhacAMaker::difficultyLevelToString(m_difficultyLevel));
	QQmlProperty::write(m_qmlGamePanel, "infoTime", remainingTimeString());
	m_score = 0;
	int msec = 0;
	if (m_difficultyLevel == WhacAMaker::Easy) {
		m_ammoLeft = easyAmmo;
		m_numMolesPerStep = easyNumMoles;
		msec = easyInterval;
	} else if (m_difficultyLevel == WhacAMaker::Medium) {
		m_ammoLeft = mediumAmmo;
		m_numMolesPerStep = mediumNumMoles;
		msec = mediumInterval;
	} else if (m_difficultyLevel == WhacAMaker::Hard) {
		m_ammoLeft = hardAmmo;
		m_numMolesPerStep = hardNumMoles;
		msec = hardInterval;
	} else {
		m_ammoLeft = testAmmo;
		msec = -1;
	}
	updateScoreAndAmmoGUI();

	// Bringing all moles down
	m_molesStatus = 0;
	updateMolesStatus();

	// Starting the timer for the game. The speed depends on the difficulty level. We don't activate the timer in test
	if (msec != -1) {
		m_gameTimer.start(msec);
		// Also calling the changeMolesStatus function immediately for the first step
		changeMolesStatus();
	}
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

	if (m_difficultyLevel == WhacAMaker::Test) {
		// Moving moles depending on joystick commands
		if (button1Pressed) {
			m_molesStatus |= (1 << moleID);
			updateMolesStatus();
		} else if (button2Pressed) {
			m_molesStatus &= ~(1 << moleID);
			updateMolesStatus();
		}
	} else {
		const bool buttonPressed = button1Pressed || button2Pressed;
		if (m_prevButtonPressed && !buttonPressed && (m_ammoLeft != 0)) {
			// An hit attempt!
			m_ammoLeft--;

			// Checking if a mole was hit
			if (((m_molesStatus >> moleID) & 1) == 1) {
				// Good shot, mole hit!
				m_score++;

				// Signal QML the mole was hit
				QMetaObject::invokeMethod(m_qmlGamePanel, "moleHit", Q_ARG(QVariant, QVariant(moleID)));

				// Bringing the mole down and updating moles status
				m_molesStatus &= ~(1 << moleID);
				updateMolesStatus();
			} else {
				// Signal QML the mole was missed
				QMetaObject::invokeMethod(m_qmlGamePanel, "moleMissed", Q_ARG(QVariant, QVariant(moleID)));
			}

			updateScoreAndAmmoGUI();
		}

		m_prevButtonPressed = buttonPressed;
	}
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
		if (m_difficultyLevel == WhacAMaker::Test) {
			newHighScore = false;
		} else {
			newHighScore = m_controller->newHighScore(m_difficultyLevel, m_score);
		}
		QMetaObject::invokeMethod(m_qmlGamePanel, "endGame", Q_ARG(QVariant, newHighScore));
	}
}

namespace {
	// A function used by random_shuffle as a source of randomness
	int randomShuffleGen(int i)
	{
		return qrand() % i;
	}
}

void GameController::changeMolesStatus()
{
	if (m_difficultyLevel != WhacAMaker::Test) {
		// Randomizing the vector of moles
		std::random_shuffle(m_moles.begin(), m_moles.end(), randomShuffleGen);

		// Initializing status
		m_molesStatus = 0;
		for (int i = 0; i < m_numMolesPerStep; i++) {
			m_molesStatus |= 1 << m_moles[i];
		}

		updateMolesStatus();
	}
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

