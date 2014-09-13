#include "gameItem.h"
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>

GameItem::GameItem(QQuickItem *parent) :
	QQuickPaintedItem(parent)
{
	setAcceptedMouseButtons(Qt::AllButtons);
}

void GameItem::paint(QPainter *painter)
{
	QPen pen(Qt::red, 2);
	painter->setPen(pen);
	painter->setRenderHints(QPainter::Antialiasing, true);
	painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
}

void GameItem::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->y() < (width() / 2)) {
		emit gameFinished(true);
	} else {
		emit gameFinished(false);
	}
}
