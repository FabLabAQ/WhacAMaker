#ifndef __MATCH_COLOR_GAME_H__
#define __MATCH_COLOR_GAME_H__

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QVector>
#include "whacAMaker.h"
#include "abstractGame.h"

/**
 * \brief The modality in which only moles of a given color should be hit
 *
 * In this modality moles come up and stay up. Only one mole has to be hit (the
 * red one). If the correct one is hit the score depends on the time the mole
 * has been up (more time means less score). If a wrong mole is hit the total
 * score is reduced. Each round moles go up and stay up until one is hit. There
 * are a fixed number of rounds
 */
class MatchColorGame : public AbstractGame
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor
	 *
	 * \param controller the game controller object
	 */
	MatchColorGame(GameController* controller);

	/**
	 * \brief Destructor
	 */
	virtual ~MatchColorGame();

	/**
	 * \brief Starts the game
	 *
	 * \param difficulty the difficulty level
	 */
	virtual void startGame(WhacAMaker::DifficultyLevel difficulty);

	/**
	 * \brief Stops the game
	 *
	 * This is called when the game should stop for external reasons
	 */
	virtual void stopGame();

	/**
	 * \brief The current joystick pointer status
	 *
	 * \param moleID the id of the mole under the pointer
	 * \param button1Pressed the status of the first button
	 * \param button2Pressed the status of the second button
	 */
	virtual void pointerStatus(int moleID, bool button1Pressed, bool button2Pressed);

	/**
	 * \brief The player score
	 *
	 * \return the player score
	 */
	virtual qreal score() const;

private slots:
	/**
	 * \brief The function called every tenth of second to increase the
	 *        elapsed time counter and update the GUI
	 */
	void timeout();

	/**
	 * \brief The slot called to start a new round of the game
	 */
	void startNewRound();

	/**
	 * \brief The slot called when the target mole is to be revealed
	 */
	void showTargetMole();

private:
	/**
	 * \brief Ends the current round
	 */
	void endRound();

	/**
	 * \brief Updates the remaining time in the GUI
	 */
	void updateGUIElapsedTime();

	/**
	 * \brief Updates the current score and round in the GUI
	 */
	void updateGUIScoreAndRound();

	/**
	 * \brief Brings moles up
	 */
	void bringMolesUp();

	/**
	 * \brief Brings all moles down and deactivates all spots
	 */
	void bringMolesDown();

	/**
	 * \brief The timer for the game time
	 *
	 * This is set to 1 sec, so that we can decrement m_remainingSeconds
	 */
	QTimer m_timer;

	/**
	 * \brief The timer for the inter-round delayr
	 */
	QTimer m_interRoundDelayTimer;

	/**
	 * \brief The timer for the delay before the mole to hit is highlighted
	 */
	QTimer m_targetMoleShownTimer;

	/**
	 * \brief When the round started
	 */
	QTime m_roundStart;

	/**
	 * \brief The current score
	 */
	qreal m_score;

	/**
	 * \brief The milliseconds that pass from the end of a round and the
	 *        start of the subsequent round
	 */
	int m_interRoundInterval;

	/**
	 * \brief The number of moles for each round
	 */
	int m_numMolesPerRound;

	/**
	 * \brief The number of rounds in the game
	 */
	int m_numRounds;

	/**
	 * \brief The current round in the game
	 */
	int m_currRound;

	/**
	 * \brief The vector of moles id. This is shuffled at each step, the
	 *        first are taken as the active moles (the number depends on the
	 *        difficulty level) and the very first one is the mole to hit
	 */
	QVector<int> m_moles;

	/**
	 * \brief True if a button was pressed when we received the previous
	 *        joystick status
	 */
	bool m_prevButtonPressed;
};

#endif
