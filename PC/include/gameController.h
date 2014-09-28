#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include <QObject>
#include <QQuickView>
#include <QTimer>
#include "whackAMaker.h"

class Controller;
class SerialCommunication;
class JoystickPointer;

/**
 * \brief The controller for the game
 *
 * This takes care of serial communication by itself. It also communicates with
 * the JoystickPointer object to get joystick movements
 */
class GameController : public QObject
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor
	 *
	 * \param controller the application controller object
	 * \param pointer the joystick pointer
	 * \param serialCommunication the object to send commands to Arduino
	 * \param view the QML viewer, passed here to get the pointer to the QML
	 *             joystick pointer
	 * \param parent the parent QObject
	 */
	GameController(Controller* controller, JoystickPointer* pointer, SerialCommunication* serialCommunication, QQuickView& view, QObject* parent = NULL);

	/**
	 * \brief Destructor
	 */
	~GameController();

	/**
	 * \brief Starts the game
	 */
	void startGame();

private slots:
	/**
	 * \brief The slot called with the new position of the joystick pointer
	 *
	 * This function is connected to the signal with absolute positions.
	 * \param x the x position of the pointer on the main view frame of
	 *          reference
	 * \param y the y position of the pointer on the main view frame of
	 *          reference
	 * \param button1Pressed whether the first button is pressed or not
	 * \param button2Pressed whether the second button is pressed or not
	 */
	void pointerPosition(qreal x, qreal y, bool button1Pressed, bool button2Pressed);

	/**
	 * \brief The function called when the game has to be terminated earlier
	 */
	void terminateGame();

	/**
	 * \brief The slot for the timer timeout
	 */
	void timeout();

	/**
	 * \brief The slot called by the game timer, to make moles appear and
	 *        disappear
	 */
	void changeMolesStatus();

private:
	/**
	 * \brief Returns a string representation for the remaining time
	 *
	 * \return a string representation for the remaining time
	 */
	QString remainingTimeString() const;

	/**
	 * \brief Updates the moles status by sending command to Arduino and
	 *        updating the qml game panel
	 */
	void updateMolesStatus();

	/**
	 * \brief Updates the qml game panel with the current score and
	 *        remaining ammo
	 */
	void updateScoreAndAmmoGUI();

	/**
	 * \brief Stops all timers and resets moles status
	 */
	void stopGame();

	/**
	 * \brief The application controller object
	 */
	Controller* const m_controller;

	/**
	 * \brief The joystick pointer
	 */
	JoystickPointer* const m_pointer;

	/**
	 * \brief The object to send commands to Arduino
	 */
	SerialCommunication* const m_serialCommunication;

	/**
	 * \brief The QML game panel object
	 */
	QObject* const m_qmlGamePanel;

	/**
	 * \brief The remaining time in seconds
	 */
	int m_remainingSeconds;

	/**
	 * \brief The timer for the game time
	 *
	 * This is set to 1 sec, so that we can decrement m_remainingSeconds
	 */
	QTimer m_timer;

	/**
	 * \brief The current difficulty level
	 */
	WhackAMaker::DifficultyLevel m_difficultyLevel;

	/**
	 * \brief The current status of moles, as sent to Arduino
	 */
	int m_molesStatus;

	/**
	 * \brief The timer for the game
	 *
	 * This is used to make moles appear/disappear
	 */
	QTimer m_gameTimer;

	/**
	 * \brief The current score
	 */
	int m_score;

	/**
	 * \brief The number of hits left
	 */
	int m_ammoLeft;

	/**
	 * \brief The number of moles for each step
	 */
	int m_numMolesPerStep;

	/**
	 * \brief The size of the game area (obtained from the qml game panel)
	 */
	qreal m_gameAreaSize;

	/**
	 * \brief True if a button was pressed when we received the previous
	 *        joystick status
	 */
	bool m_prevButtonPressed;

	/**
	 * \brief The vector of moles id. This is shuffled at each step and the
	 *        first are takes as the active moles (the number depends on the
	 *        difficulty level
	 */
	QVector<int> m_moles;
};

#endif
