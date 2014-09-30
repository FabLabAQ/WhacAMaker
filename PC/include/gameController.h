#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include <QObject>
#include <QQuickView>
#include <QTimer>
#include "whacAMaker.h"

class Controller;
class AbstractGame;
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
	virtual ~GameController();

	/**
	 * \brief Starts the game
	 */
	void startGame();

	/**
	 * \brief Stops all timers and resets moles status
	 *
	 * \param checkHighScore if true checks if score is a highscore,
	 *                       otherwise no check is performed and score is
	 *                       not saved
	 */
	void stopGame(bool checkHighScore);

	/**
	 * \brief Updates the moles status by sending command to Arduino
	 *
	 * \param status the new mole status
	 */
	void updateArduinoMolesStatus(int status);

	/**
	 * \brief Returns a const pointer to the application controller object
	 *
	 * \return a const pointer to the application controller object
	 */
	const Controller* controller() const
	{
		return m_controller;
	}

	/**
	 * \brief Returns a pointer to the application controller object
	 *
	 * \return a pointer to the application controller object
	 */
	Controller* controller()
	{
		return m_controller;
	}

	/**
	 * \brief Returns a const pointer to the joystick pointer
	 *
	 * \return a const pointer to the joystick pointer
	 */
	const JoystickPointer* pointer() const
	{
		return m_pointer;
	}

	/**
	 * \brief Returns a pointer to the joystick pointer
	 *
	 * \return a pointer to the joystick pointer
	 */
	JoystickPointer* pointer()
	{
		return m_pointer;
	}

	/**
	 * \brief Returns a const pointer to the object to send commands to
	 *        Arduino
	 *
	 * \return a const pointer to the object to send commands to Arduino
	 */
	const SerialCommunication* serialCommunication() const
	{
		return m_serialCommunication;
	}

	/**
	 * \brief Returns a pointer to the object to send commands to Arduino
	 *
	 * \return a pointer to the object to send commands to Arduino
	 */
	SerialCommunication* serialCommunication()
	{
		return m_serialCommunication;
	}

	/**
	 * \brief Returns a const pointer to the QML game panel object
	 *
	 * \return a const pointer to the QML game panel object
	 */
	const QObject* qmlGamePanel() const
	{
		return m_qmlGamePanel;
	}

	/**
	 * \brief Returns a pointer to the QML game panel object
	 *
	 * \return a pointer to the QML game panel object
	 */
	QObject* qmlGamePanel()
	{
		return m_qmlGamePanel;
	}

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

private:
	/**
	 * \brief Creates a game depending on the selected modality
	 *
	 * This doesn't start the game. The pointer to the created object is
	 * m_game. If a game existed, it is deleted
	 */
	void gameFactory();

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
	 * \brief The current game
	 */
	AbstractGame* m_game;

	/**
	 * \brief The current game modality
	 */
	WhacAMaker::GameType m_gameType;

	/**
	 * \brief The current difficulty level
	 */
	WhacAMaker::DifficultyLevel m_difficultyLevel;

	/**
	 * \brief The size of the game area (obtained from the qml game panel)
	 */
	qreal m_gameAreaSize;
};

#endif
