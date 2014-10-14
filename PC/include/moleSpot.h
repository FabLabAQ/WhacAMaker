#ifndef __MOLE_SPOT_H__
#define __MOLE_SPOT_H__

#include <QQuickPaintedItem>
#include <QColor>

/**
 * \brief The QML item paiting a spot on the mole
 *
 * This is not implemented in pure QML because using canvas with animations
 * seems to slow the application down
 */
class MoleSpot : public QQuickPaintedItem
{
	Q_OBJECT
	Q_PROPERTY(qreal angle READ angle WRITE setAngle NOTIFY angleChanged)
	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(qreal spotSize READ spotSize WRITE setSpotSize NOTIFY spotSizeChanged)

public:
	/**
	 * \brief Constructor
	 *
	 * \param parent the parent item
	 */
	MoleSpot(QQuickItem *parent = NULL);

	/**
	 * \brief Destructor
	 */
	~MoleSpot();

	/**
	 * \brief The function performing the actual drawing
	 *
	 * \param painter the object to use for drawing
	 */
	virtual void paint(QPainter *painter);

	/**
	 * \brief Sets the angle
	 *
	 * This triggers a repaint
	 * \param angle the new angle
	 */
	void setAngle(qreal angle);

	/**
	 * \brief Returns the current angle
	 *
	 * \return the current angle
	 */
	qreal angle() const
	{
		return m_angle;
	}

	/**
	 * \brief Sets the color
	 *
	 * This triggers a repaint
	 * \param color the new color
	 */
	void setColor(QColor color);

	/**
	 * \brief Returns the current color
	 *
	 * \return the current color
	 */
	QColor color() const
	{
		return m_color;
	}

	/**
	 * \brief Sets the spot size
	 *
	 * This triggers a repaint
	 * \param spotSize the new spot size as a portion of total width (this
	 *                 should be a value between 0.0 and 1.0)
	 */
	void setSpotSize(qreal spotSize);

	/**
	 * \brief Returns the current spot size
	 *
	 * \return the current spot size
	 */
	qreal spotSize() const
	{
		return m_spotSize;
	}

signals:
	/**
	 * \brief The signal emitted when the angle changes
	 */
	void angleChanged();

	/**
	 * \brief The signal emitted when the color changes
	 */
	void colorChanged();

	/**
	 * \brief The signal emitted when the spot size changes
	 */
	void spotSizeChanged();

private:
	/**
	 * \brief The current angle
	 */
	qreal m_angle;

	/**
	 * \brief The color
	 */
	QColor m_color;

	/**
	 * \brief The diameter of the spot as a portion of width
	 */
	qreal m_spotSize;
};

#endif
