#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <QObject>
#include <QQuickView>
#include <QSettings>
#include <QList>
#include <QVariant>
#include "gameController.h"
#include "serialCommunication.h"
#include "joystickPointer.h"
#include "whackAMaker.h"

/**
 * \brief The main controller of the game
 *
 * This class takes care of controlling the game. It connects to signals from
 * QML items, starts the thread to communicate with Arduino and reads/store
 * configuration parameters and scores
 */
class Controller : public QObject
{
	Q_OBJECT

	/**
	 * \brief The current application status
	 */
	enum Status {
		Menu,
		JoystickCalibration,
		Game
	};

public:
	/**
	 * \brief Constructor
	 *
	 * \param view the object displaying the QML scene and starting the QML
	 *             engine
	 * \param parent the parent object
	 */
	Controller(QQuickView& view, QObject* parent = NULL);

	/**
	 * \brief Destructor
	 */
	virtual ~Controller();

	/**
	 * \brief Returns a const reference to the QML view
	 *
	 * \return a const reference to the QML view
	 */
	const QQuickView& getView() const
	{
		return m_view;
	}

	/**
	 * \brief Returns a reference to the QML view
	 *
	 * \return a reference to the QML view
	 */
	QQuickView& view()
	{
		return m_view;
	}

	/**
	 * \brief If score is going to be a highscore for the given level,
	 *        returns true and uses it as the score of the next player
	 *
	 * \param level the difficulty level
	 * \param score the score
	 * \return true if score is in the highscores
	 */
	bool newHighScore(WhackAMaker::DifficultyLevel level, double score);

	/**
	 * \brief The function called when a new command is received
	 *
	 * Here we call methods of the SerialCommunication object to obtain the
	 * command that has been received
	 */
	void commandReceived();

private slots:
	/**
	 * \brief This is the slot called when configuration parameters are
	 *        saved
	 *
	 * \param obj the object with configuration parameters
	 */
	void saveConfigurationParameters();

	/**
	 * \brief This is the slot called when a player has entered its name
	 *
	 * \param name the name of the player
	 */
	void savePlayerName(const QString& name);

	/**
	 * \brief The slot called when joystick calibration starts
	 */
	void joystickCalibrationStarted();

	/**
	 * \brief The slot called when joystick calibration ends
	 */
	void joystickCalibrationEnded();

	/**
	 * \brief The slot called with the new position of the joystick pointer
	 *        on the screen
	 *
	 * This function emulates mouse clicks if buttons are pressed
	 * \param x the x position of the pointer on the main view frame of
	 *          reference
	 * \param y the y position of the pointer on the main view frame of
	 *          reference
	 * \param button1Pressed whether the first button is pressed or not
	 * \param button2Pressed whether the second button is pressed or not
	 */
	void pointerPosition(qreal x, qreal y, bool button1Pressed, bool button2Pressed);

	/**
	 * \brief The slot called when the game starts
	 */
	void gameStarted();

	/**
	 * \brief The slot called when the game ends
	 */
	void gameFinished();

private:
	/**
	 * \brief Restores parameters in the configuration parameters QML object
	 */
	void restoreParameters();

	/**
	 * \brief Restores the highscores in the panel for the given level
	 *
	 * \param level the difficulty level whose highscores to restore
	 */
	void restoreHighScores(WhackAMaker::DifficultyLevel level);

	/**
	 * \brief Copies a value from settings to an QML item
	 *
	 * \param item the QML item whose property we write
	 * \param propName the name of the property to write. The name of the
	 *                 property is "\<propName\>Value" and the name of the
	 *                 setting is "configuration/\<propName\>"
	 */
	void copyPropertyToItem(QObject* item, QString propName);

	/**
	 * \brief Copies a value from QML item to settings if valid, restores
	 *        a valid value in the QML item otherwise
	 *
	 * \param item the QML item whose property we read
	 * \param propName the name of the property to read. The name of the
	 *                 property is "\<propName\>Value" and the name of the
	 *                 setting is "configuration/\<propName\>"
	 * \return true if the user value was valid, false otherwise
	 */
	bool copyPropertyToSettings(QObject* item, QString propName);

	/**
	 * \brief Returns the highscores and players for the given level loading
	 *        them from m_setting
	 *
	 * \param level the level whose highscores and players to get
	 * \param highscores the vector to fill with highscores
	 * \param players the vector to fill with players
	 * \param levelName the vector with a string representation of level
	 */
	void getHighScoresFromSettings(WhackAMaker::DifficultyLevel level, QList<QVariant>& highscores, QList<QVariant>& players, QString& levelName);

	/**
	 * \brief Sets the serial port in the serial communication object
	 *        reading it from settings
	 */
	void setSerialPort();

	/**
	 * \brief The current status
	 */
	Status m_status;

	/**
	 * \brief The object with settings for the application
	 */
	QSettings m_settings;

	/**
	 * \brief The object displaying the QML scene and starting the QML
	 *        engine
	 */
	QQuickView& m_view;

	/**
	 * \brief The object taking care of the communication with Arduino
	 */
	SerialCommunication m_serialCom;

	/**
	 * \brief The object managing the joystick pointer
	 */
	JoystickPointer m_joystickPointer;

	/**
	 * \brief The object controlling the game
	 */
	GameController m_gameController;

	/**
	 * \brief The level of the next highscore
	 */
	WhackAMaker::DifficultyLevel m_nextScoreLevel;

	/**
	 * \brief The score of the next highscore
	 */
	double m_nextScore;

	/**
	 * \brief The previous status of button 1 (whether pressed or not)
	 */
	bool m_button1PrevStatus;

	/**
	 * \brief The previous status of button 2 (whether pressed or not)
	 */
	bool m_button2PrevStatus;
};

#endif
