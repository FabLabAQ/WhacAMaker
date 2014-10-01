#ifndef __MOLE_SPOT_H__
#define __MOLE_SPOT_H__

#include <QQuickPaintedItem>
#include <QTimer>

/**
 * \brief The QML item paiting a spot on the mole
 *
 * This is not implemented in pure QML because using canvas with animations
 * seems to slow the application
 */
class MoleSpot : public QQuickPaintedItem
{
	Q_OBJECT

public:
	/**
	 * \brief The function performing the actual drawing
	 *
	 * \param painter the object to use for drawing
	 */
	virtual void paint(QPainter *painter) {}
};

// class Controller;
// class SerialCommunication;
//
// /**
//  * \brief The QML item with the game screen
//  */
// class GameItem : public QQuickPaintedItem
// {
// 	Q_OBJECT
// 	Q_ENUMS(DifficultyLevel)
// 	Q_PROPERTY(DifficultyLevel difficultyLevel READ difficultyLevel WRITE setDifficultyLevel NOTIFY difficultyLevelChanged)
//
// public:
// 	/**
// 	 * \brief The difficulty levels
// 	 */
// 	enum DifficultyLevel {
// 		Easy,
// 		Medium,
// 		Hard
// 	};
//
// public:
// 	/**
// 	 * \brief Constructor
// 	 *
// 	 * \param parent the parent item
// 	 */
// 	GameItem(QQuickItem *parent = NULL);
//
// 	/**
// 	 * \brief Sets the controller object
// 	 *
// 	 * \param controller the controller object
// 	 */
// 	void setController(Controller* controller);
//
// 	/**
// 	 * \brief The function performing the actual drawing
// 	 *
// 	 * \param painter the object to use for drawing
// 	 */
// 	virtual void paint(QPainter *painter);
//
// 	/**
// 	 * \brief Returns the current difficulty level
// 	 *
// 	 * \return the current difficulty level
// 	 */
// 	DifficultyLevel difficultyLevel() const
// 	{
// 		return m_level;
// 	}
//
// 	/**
// 	 * \brief Sets the new difficulty level
// 	 *
// 	 * \param level the new difficulty level
// 	 */
// 	void setDifficultyLevel(DifficultyLevel newLevel);
//
// public slots:
// 	/**
// 	 * \brief Call to start the game
// 	 */
// 	void startGame();
//
// signals:
// 	/**
// 	 * \brief The signal emitted when the game finishes
// 	 *
// 	 * \param newHighScore if true the player scored a new high score
// 	 */
// 	void gameFinished(bool newHighScore);
//
// 	/**
// 	 * \brief The signal emitted when the difficulty level changes
// 	 */
// 	void difficultyLevelChanged();
//
// protected:
// 	/**
// 	 * \brief The function called when the used performs a double click on
// 	 *        the item
// 	 *
// 	 * \param event the object describing the event
// 	 */
// 	virtual void mouseDoubleClickEvent(QMouseEvent *event);
//
// private slots:
// 	/**
// 	 * \brief The slot called by the game timer
// 	 */
// 	void timeout();
//
// private:
// 	/**
// 	 * \brief The controller object
// 	 */
// 	Controller* m_controller;
//
// 	/**
// 	 * \brief The difficulty level of the game
// 	 */
// 	DifficultyLevel m_level;
//
// 	/**
// 	 * \brief The level static text
// 	 */
// 	QStaticText m_levelText;
//
// 	/**
// 	 * \brief The easy level static text
// 	 */
// 	QStaticText m_easyLevelText;
//
// 	/**
// 	 * \brief The medium level static text
// 	 */
// 	QStaticText m_mediumLevelText;
//
// 	/**
// 	 * \brief The hard level static text
// 	 */
// 	QStaticText m_hardLevelText;
//
// 	/**
// 	 * \brief The score static text
// 	 */
// 	QStaticText m_scoreText;
//
// 	/**
// 	 * \brief The remaining munitions static text
// 	 */
// 	QStaticText m_ammoText;
//
// 	/**
// 	 * \brief The remaining time static text
// 	 */
// 	QStaticText m_timeLeftText;
//
// 	/**
// 	 * \brief The game timer
// 	 */
// 	QTimer m_timer;
//
// 	/**
// 	 * \brief The remaining seconds
// 	 */
// 	int m_remainingSeconds;
// };

#endif
