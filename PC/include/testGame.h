#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include <QObject>
#include "whacAMaker.h"
#include "abstractGame.h"

/**
 * \brief The test modality
 *
 * In this modality the player can select which mole to bring up (with button1)
 * or down (with button2). The game terminates when both buttons are pressed
 * together. This is only to testing purpouse, no score is assigned. Also the
 * difficulty level is ignored
 */
class TestGame : public AbstractGame
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor
	 *
	 * \param controller the game controller object
	 */
	TestGame(GameController* controller);

	/**
	 * \brief Destructor
	 */
	virtual ~TestGame();

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

#endif
