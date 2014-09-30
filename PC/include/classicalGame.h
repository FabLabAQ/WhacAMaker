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
	 * \brief The current joystick pointer status
	 *
	 * \param moleID the id of the mole under the pointer
	 * \param button1Pressed the status of the first button
	 * \param button2Pressed the status of the second button
	 */
	virtual void pointerStatus(int moleID, bool button1Pressed, bool button2Pressed);
};

#endif
