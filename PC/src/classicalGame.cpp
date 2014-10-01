#include "classicalGame.h"
#include "gameController.h"
#include "helpers.h"
#include <QQmlProperty>
#include <QDateTime>
#include <QStringList>
#include <algorithm>

// Useful constants
namespace {
	// How many seconds the game lasts
	const int gameDuration = 60;
	// The interval between moles changes in various difficulty levels in milliseconds
	const int easyInterval = 5000;
	const int mediumInterval = 3000;
	const int hardInterval = 1000;
	// The initial number of hits in various difficulty levels
	const int easyAmmo = 100;
	const int mediumAmmo = 80;
	const int hardAmmo = 50;
	// The number of moles at each step for various difficulty levels
	const int easyNumMoles = 6;
	const int mediumNumMoles = 4;
	const int hardNumMoles = 4;
}

ClassicalGame::ClassicalGame(GameController* controller)
	: AbstractGame(controller)
	, m_timer()
	, m_gameTimer()
	, m_molesStatus(0)
	, m_remainingSeconds(0)
	, m_score(0.0)
	, m_ammoLeft(0)
	, m_numMolesPerStep(0)
	, m_moles(9)
	, m_prevButtonPressed(false)
{
	// Connecting timer signals
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
	connect(&m_gameTimer, SIGNAL(timeout()), this, SLOT(changeMolesStatus()));

	// We also need to initialize the random number generator
	qsrand(uint(QDateTime::currentMSecsSinceEpoch() / 1000));

	// Initializig the vector of moles ids
	for (int i = 0; i < m_moles.size(); ++i) {
		m_moles[i] = i;
	}
}

ClassicalGame::~ClassicalGame()
{
	// Nothing to do here
}

void ClassicalGame::startGame(WhacAMaker::DifficultyLevel difficulty)
{
	// Bringing all moles down
	m_molesStatus = 0;
	updateMolesStatus();

	// Setting fields for information to show and setting spot color to yellow
	QStringList informationFields = QStringList() << "Punteggio" << "Colpi Rimasti" << "Tempo rimanente";
	QQmlProperty::write(m_controller->qmlGamePanel(), "informationFields", informationFields);
	QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "changeAllMolesSpotColor", Q_ARG(QVariant, QColor(Qt::yellow)));

	// Setting al variables to their initial status depending on the difficulty level
	m_remainingSeconds = gameDuration;
	m_score = 0;
	int gameTimerDelay = 0;
	if (difficulty == WhacAMaker::Easy) {
		m_ammoLeft = easyAmmo;
		m_numMolesPerStep = easyNumMoles;
		gameTimerDelay = easyInterval;
	} else if (difficulty == WhacAMaker::Medium) {
		m_ammoLeft = mediumAmmo;
		m_numMolesPerStep = mediumNumMoles;
		gameTimerDelay = mediumInterval;
	} else if (difficulty == WhacAMaker::Hard) {
		m_ammoLeft = hardAmmo;
		m_numMolesPerStep = hardNumMoles;
		gameTimerDelay = hardInterval;
	}

	// Setting initial value of information
	updateGUIRemainingTime();
	updateGUIScoreAndAmmo();

	// Starting both timers
	m_timer.start(1000); // This is not very accurate (each timeout signal has 5% tolerance), but for he moment it is enough
	m_gameTimer.start(gameTimerDelay);

	// Also calling the changeMolesStatus function immediately for the first step
	changeMolesStatus();
}

void ClassicalGame::stopGame()
{
	m_timer.stop();
	m_gameTimer.stop();

	// Ending game with no highscore
	m_controller->stopGame(false);
}

void ClassicalGame::pointerStatus(int moleID, bool button1Pressed, bool button2Pressed)
{
	const bool buttonPressed = button1Pressed || button2Pressed;
	if (m_prevButtonPressed && !buttonPressed && (m_ammoLeft != 0)) {
		// An hit attempt!
		m_ammoLeft--;

		// Checking if a mole was hit
		if (((m_molesStatus >> moleID) & 1) == 1) {
			// Good shot, mole hit!
			m_score++;

			// Signal QML the mole was hit
			QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "moleHit", Q_ARG(QVariant, QVariant(moleID)));

			// Bringing the mole down and updating moles status
			m_molesStatus &= ~(1 << moleID);
			updateMolesStatus();
		} else {
			// Signal QML the mole was missed
			QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "moleMissed", Q_ARG(QVariant, QVariant(moleID)));
		}

		updateGUIScoreAndAmmo();
	}

	m_prevButtonPressed = buttonPressed;
}

qreal ClassicalGame::score() const
{
	return m_score;
}

void ClassicalGame::timeout()
{
	m_remainingSeconds--;

	// Updating qml property
	updateGUIRemainingTime();

	// Checking if game has ended
	if ((m_remainingSeconds == 0) || (m_ammoLeft == 0)) {
		m_timer.stop();
		m_gameTimer.stop();

		m_controller->stopGame(true);
	}
}

void ClassicalGame::changeMolesStatus()
{
	// Randomizing the vector of moles
	std::random_shuffle(m_moles.begin(), m_moles.end(), randomShuffleGen);

	// Initializing status
	m_molesStatus = 0;
	for (int i = 0; i < m_numMolesPerStep; i++) {
		m_molesStatus |= 1 << m_moles[i];
	}

	updateMolesStatus();
}

void ClassicalGame::updateGUIRemainingTime()
{
	QString timeString = QString("%1:%2").arg(m_remainingSeconds / 60).arg(m_remainingSeconds % 60, 2, 10, QChar('0'));

	// The remaining time has index 3 in the information fields list
	QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "setInformationFieldValue", Q_ARG(QVariant, 3), Q_ARG(QVariant, timeString));
}

void ClassicalGame::updateGUIScoreAndAmmo()
{
	// The score and remaining ammo have index 1 and 2 respectively in the information fields list
	QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "setInformationFieldValue", Q_ARG(QVariant, 1), Q_ARG(QVariant, QString::number(m_score)));
	QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "setInformationFieldValue", Q_ARG(QVariant, 2), Q_ARG(QVariant, QString::number(m_ammoLeft)));
}

void ClassicalGame::updateMolesStatus()
{
	// Sending command to Arduino
	m_controller->updateArduinoMolesStatus(m_molesStatus);

	// Updating qml game panel
	QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "changeMoleSpotStatus", Q_ARG(QVariant, QVariant(m_molesStatus)));
}
