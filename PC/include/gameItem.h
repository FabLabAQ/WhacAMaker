#include <QQuickPaintedItem>

/**
 * \brief The QML item with the game screen
 */
class GameItem : public QQuickPaintedItem
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor
	 *
	 * \parent the parent item
	 */
	GameItem(QQuickItem *parent = NULL);

	/**
	 * \brief The function performing the actual drawing
	 *
	 * \param painter the object to use for drawing
	 */
	virtual void paint(QPainter *painter);

signals:
	/**
	 * \brief The signal emitted when the game finishes
	 *
	 * \param newHighScore if true the player scored a new high score
	 */
	void gameFinished(bool newHighScore);

protected:
	/**
	 * \brief The function called when the used performs a double click on
	 *        the item
	 *
	 * \param event the object describing the event
	 */
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
};
