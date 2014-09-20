#ifndef __GAME_ITEM_H__
#define __GAME_ITEM_H__

#include <QQuickPaintedItem>

class Controller;
class SerialCommunication;

/**
 * \brief The QML item with the game screen
 */
class GameItem : public QQuickPaintedItem
{
	Q_OBJECT
	Q_ENUMS(DifficultyLevel)
	Q_PROPERTY(DifficultyLevel difficultyLevel READ difficultyLevel WRITE setDifficultyLevel NOTIFY difficultyLevelChanged)

public:
	/**
	 * \brief The difficulty levels
	 */
	enum DifficultyLevel {
		Easy,
		Medium,
		Hard
	};

public:
	/**
	 * \brief Constructor
	 *
	 * \param parent the parent item
	 */
	GameItem(QQuickItem *parent = NULL);

	/**
	 * \brief Sets the controller object
	 *
	 * \param controller the controller object
	 */
	void setController(Controller* controller);

	/**
	 * \brief The function performing the actual drawing
	 *
	 * \param painter the object to use for drawing
	 */
	virtual void paint(QPainter *painter);

	/**
	 * \brief Returns the current difficulty level
	 *
	 * \return the current difficulty level
	 */
	DifficultyLevel difficultyLevel() const
	{
		return m_level;
	}

	/**
	 * \brief Sets the new difficulty level
	 *
	 * \param level the new difficulty level
	 */
	void setDifficultyLevel(DifficultyLevel newLevel);

signals:
	/**
	 * \brief The signal emitted when the game finishes
	 *
	 * \param newHighScore if true the player scored a new high score
	 */
	void gameFinished(bool newHighScore);

	/**
	 * \brief The signal emitted when the difficulty level changes
	 */
	void difficultyLevelChanged();

protected:
	/**
	 * \brief The function called when the used performs a double click on
	 *        the item
	 *
	 * \param event the object describing the event
	 */
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
	/**
	 * \brief The controller object
	 */
	Controller* m_controller;

	/**
	 * \brief The difficulty level of the game
	 */
	DifficultyLevel m_level;
};

#endif
