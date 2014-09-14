#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <QObject>
#include <QQuickView>
#include <QSettings>
#include "gameItem.h"

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
	 * \brief If score is going to be a highscore for the given level,
	 *        returns true and used it as the score of the next player
	 *
	 * \param level the difficulty level
	 * \param score the score
	 * \return true if score is in the highscores
	 */
	bool newHighScore(GameItem::DifficultyLevel level, double score);

protected slots:
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

protected:
	/**
	 * \brief Restores parameters in the configuration parameters QML object
	 */
	void restoreParameters();

	/**
	 * \brief Returns a pointer to the QML object with configuration
	 *        parameters
	 *
	 * \return a pointer to the QML object with configuration parameters
	 */
	QObject* qmlConfigurationParametersObject();

	/**
	 * \brief Returns a pointer to the game object
	 *
	 * \return a pointer to the game object
	 */
	GameItem* qmlGameObject();

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
	 */
	void copyPropertyToSettings(QObject* item, QString propName);

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
	 * \brief The level of the next highscore
	 */
	GameItem::DifficultyLevel m_nextScoreLevel;

	/**
	 * \brief The score of the next highscore
	 */
	double m_nextScore;
};

#endif
