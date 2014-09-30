#ifndef __CLASSICAL_GAME_H__
#define __CLASSICAL_GAME_H__

#include <QObject>
#include "whacAMaker.h"
#include "abstractGame.h"

/**
 * \brief The classical modality
 *
 * In this modality moles come up and stay up for a certain amount of time, then
 * they go down. You have to hit as many as possible. There also is a limited
 * amount of "ammunitions"
 */
class ClassicalGame : public AbstractGame
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor
	 *
	 * \param controller the game controller object
	 */
	ClassicalGame(GameController* controller);

	/**
	 * \brief Destructor
	 */
	virtual ~ClassicalGame();

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
};






// 	/**
// 	 * \brief The application controller object
// 	 */
// 	Controller* const m_controller;
//
// 	/**
// 	 * \brief The joystick pointer
// 	 */
// 	JoystickPointer* const m_pointer;
//
// 	/**
// 	 * \brief The object to send commands to Arduino
// 	 */
// 	SerialCommunication* const m_serialCommunication;
//
// 	/**
// 	 * \brief The QML game panel object
// 	 */
// 	QObject* const m_qmlGamePanel;
//
// 	/**
// 	 * \brief The current game
// 	 */
// 	AbstractGame* m_game;
//
// 	/**
// 	 * \brief The current game modality
// 	 */
// 	WhacAMaker::GameType m_gameType;
//
// 	/**
// 	 * \brief The current difficulty level
// 	 */
// 	WhacAMaker::DifficultyLevel m_difficultyLevel;
//
// 	/**
// 	 * \brief The remaining time in seconds
// 	 */
// 	int m_remainingSeconds;
//
// 	/**
// 	 * \brief The timer for the game time
// 	 *
// 	 * This is set to 1 sec, so that we can decrement m_remainingSeconds
// 	 */
// 	QTimer m_timer;
//
// 	/**
// 	 * \brief The current status of moles, as sent to Arduino
// 	 */
// 	int m_molesStatus;
//
// 	/**
// 	 * \brief The timer for the game
// 	 *
// 	 * This is used to make moles appear/disappear
// 	 */
// 	QTimer m_gameTimer;
//
// 	/**
// 	 * \brief The current score
// 	 */
// 	int m_score;
//
// 	/**
// 	 * \brief The number of hits left
// 	 */
// 	int m_ammoLeft;
//
// 	/**
// 	 * \brief The number of moles for each step
// 	 */
// 	int m_numMolesPerStep;
//
// 	/**
// 	 * \brief True if a button was pressed when we received the previous
// 	 *        joystick status
// 	 */
// 	bool m_prevButtonPressed;
//
// 	/**
// 	 * \brief The vector of moles id. This is shuffled at each step and the
// 	 *        first are takes as the active moles (the number depends on the
// 	 *        difficulty level
// 	 */
// 	QVector<int> m_moles;

#endif
