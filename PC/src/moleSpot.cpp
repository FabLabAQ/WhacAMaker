#include "moleSpot.h"
#include <QPen>
#include <QBrush>
#include <QPainter>

MoleSpot::MoleSpot(QQuickItem *parent)
	: QQuickPaintedItem(parent)
	, m_angle(0.0)
	, m_color(Qt::white)
	, m_spotSize(0.45)
{
}

MoleSpot::~MoleSpot()
{
	// Nothing to do here
}

void MoleSpot::paint(QPainter *painter)
{
	// Activating antialiasing
	painter->setRenderHints(QPainter::Antialiasing, true);

	// The dimension of the spot. We should have a square size, but just to be sure we take
	// the smaller dimension and multiply it by m_spotSize
	const qreal actualSpotSize = ((width() < height()) ? width() : height()) * m_spotSize;
	const QRectF spotRect((width() - actualSpotSize) / 2.0, (height() - actualSpotSize) / 2.0, actualSpotSize, actualSpotSize);

	// Now setting pen and brush
	const QPen pen(m_color, actualSpotSize / 20.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	const QBrush brush(m_color);
	painter->setPen(pen);
	painter->setBrush(brush);

	// Now drawing 3/4 of a circle
	const int startAngle = m_angle * 16;
	const int spanAngle = 270 * 16;
	painter->drawPie(spotRect, startAngle, spanAngle);
}

void MoleSpot::setAngle(qreal angle)
{
	if (angle != m_angle) {
		m_angle = angle;
		update();
		emit angleChanged();
	}
}

void MoleSpot::setColor(QColor color)
{
	if (color != m_color) {
		m_color = color;
		update();
		emit colorChanged();
	}
}

void MoleSpot::setSpotSize(qreal spotSize)
{
	if (spotSize != m_spotSize) {
		m_spotSize = spotSize;
		update();
		emit spotSizeChanged();
	}
}
