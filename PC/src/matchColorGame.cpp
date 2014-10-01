#include "matchColorGame.h"
#include "gameController.h"
#include "helpers.h"
#include <QQmlProperty>
#include <QDateTime>
#include <QStringList>
#include <algorithm>

// Useful constants
namespace {
	// The time interval between rounds in milliseconds
	const int easyInterRoundInterval = 3000;
	const int mediumInterRoundInterval = 2000;
	const int hardInterRoundInterval = 1000;
	// The number of rounds to do
	const int easyNumRounds = 5;
	const int mediumNumRounds = 7;
	const int hardNumRounds = 9;
	// The number of moles at each step for various difficulty levels
	const int easyNumMoles = 5;
	const int mediumNumMoles = 5;
	const int hardNumMoles = 5;
	// Each how many milliseconds the time displayed on the gui is updated
	const int timeDisplayUpdateInterval = 100;
}

MatchColorGame::MatchColorGame(GameController* controller)
	: AbstractGame(controller)
	, m_timer()
	, m_interRoundDelayTimer()
	, m_roundStart()
	, m_score(0.0)
	, m_interRoundInterval(0)
	, m_numMolesPerRound(0)
	, m_numRounds(0)
	, m_curRound(0)
	, m_moles(9)
	, m_prevButtonPressed(false)
{
	// The inter-round delay timer is single-shot
	m_interRoundDelayTimer.setSingleShot(true);

	// Connecting timer signals
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
	connect(&m_interRoundDelayTimer, SIGNAL(timeout()), this, SLOT(startNewRound()));

	// We also need to initialize the random number generator
	qsrand(uint(QDateTime::currentMSecsSinceEpoch() / 1000));

	// Initializig the vector of moles ids
	for (int i = 0; i < m_moles.size(); ++i) {
		m_moles[i] = i;
	}
}

MatchColorGame::~MatchColorGame()
{
	// Nothing to do here
}

void MatchColorGame::startGame(WhacAMaker::DifficultyLevel difficulty)
{
	// Bringing all moles down
	bringMolesDown();

	// Setting fields for information to show and setting spot color to yellow. The selected mole color will be set to red
	// when we start
	QStringList informationFields = QStringList() << "Manches" << "Punteggio" << "Tempo trascorso manches";
	QQmlProperty::write(m_controller->qmlGamePanel(), "informationFields", informationFields);
	QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "changeAllMolesSpotColor", Q_ARG(QVariant, QColor(Qt::yellow)));

	// Setting al variables to their initial status depending on the difficulty level
	m_curRound = 0;
	m_score = 0;
	if (difficulty == WhacAMaker::Easy) {
		m_interRoundInterval = easyInterRoundInterval;
		m_numMolesPerRound = easyNumMoles;
		m_numRounds = easyNumRounds;
	} else if (difficulty == WhacAMaker::Medium) {
		m_interRoundInterval = mediumInterRoundInterval;
		m_numMolesPerRound = mediumNumMoles;
		m_numRounds = mediumNumRounds;
	} else if (difficulty == WhacAMaker::Hard) {
		m_interRoundInterval = hardInterRoundInterval;
		m_numMolesPerRound = hardNumMoles;
		m_numRounds = hardNumRounds;
	}

	// Setting initial value of information
	updateGUIRemainingTime();
	updateGUIScoreAndRound();

	// Starting both timers
	m_timer.start(timeDisplayUpdateInterval);
	m_interRoundDelayTimer.start(m_interRoundInterval);
}

void MatchColorGame::stopGame()
{
	m_timer.stop();
	m_interRoundDelayTimer.stop();

	// Ending game with no highscore
	m_controller->stopGame(false);
}

void MatchColorGame::pointerStatus(int moleID, bool button1Pressed, bool button2Pressed)
{
	const bool buttonPressed = button1Pressed || button2Pressed;
	if (m_prevButtonPressed && !buttonPressed) {
		// An hit attempt!

		// First checking if a mole was hit
		bool moleHit = false;
		for (int i = 0; i < m_numMolesPerRound; i++) {
			if (m_moleID == m_moles[i]) {
				moleHit = true;
				break;
			}
		}

		if (moleHit) {
			// Checking if the target mole was hit
			if (moleID == m_moles[0]) {
				// Good shot, mole hit!
				m_score += DIPENDE DA TEMPO IMPIEGATO;

				// Signal QML the mole was hit
				QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "moleHit", Q_ARG(QVariant, QVariant(moleID)));
			} else {
				// Ouch, wrong mole
				m_score -= ???;

				// Signal QML a wrong hit
				QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "moleWrongHit", Q_ARG(QVariant, QVariant(moleID)));
			}

			// Bringing down all moles
			bringMolesDown();

			// Starting the timer with the inter-round delay
			m_interRoundDelayTimer.start(m_interRoundInterval);

			// Updating score, round and remaining time
			updateGUIRemainingTime();
			updateGUIScoreAndRound();
		} else {
			// Signal QML the mole was missed
			QMetaObject::invokeMethod(m_controller->qmlGamePanel(), "moleMissed", Q_ARG(QVariant, QVariant(moleID)));
		}
	}

	m_prevButtonPressed = buttonPressed;
}

qreal MatchColorGame::score() const
{
	return m_score;
}

void MatchColorGame::timeout()
{
#warning TODO!!!
	increase gui time, use m_roundStart
}

void MatchColorGame::startNewRound()
{
#warning TODO!!!
}

void MatchColorGame::updateGUIRemainingTime()
{
#warning TODO!!!
}

void MatchColorGame::updateGUIScoreAndRound()
{
#warning TODO!!!
}

void MatchColorGame::bringMolesUp()
{
#warning TODO!!!
}

void MatchColorGame::bringMolesDown()
{
#warning TODO!!!
}
