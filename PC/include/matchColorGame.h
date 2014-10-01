#ifndef __MATCH_COLOR_GAME_H__
#define __MATCH_COLOR_GAME_H__

#include <QObject>
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
};

#endif
