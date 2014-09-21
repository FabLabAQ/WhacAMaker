#include "gameItem.h"
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include "myRuntimeException.h"
#include "controller.h"

GameItem::GameItem(QQuickItem *parent)
	: QQuickPaintedItem(parent)
	, m_controller(NULL)
	, m_level(Easy)
{
	setAcceptedMouseButtons(Qt::AllButtons);
}

void GameItem::setController(Controller* controller)
{
	m_controller = controller;
}

void GameItem::paint(QPainter *painter)
{
	QPen pen(Qt::red, 2);
	if (m_level == Easy) {
		pen.setColor(Qt::red);
	} else if (m_level == Medium) {
		pen.setColor(Qt::green);
	} else {
		pen.setColor(Qt::blue);
	}
	painter->setPen(pen);
	painter->setRenderHints(QPainter::Antialiasing, true);
	painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
}

void GameItem::setDifficultyLevel(DifficultyLevel newLevel)
{
	if (newLevel != m_level) {
		m_level = newLevel;
		update();
		emit difficultyLevelChanged();
	}
}

void GameItem::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (m_controller == NULL) {
		throwMyRuntimeException("Controller not set in GameItem (in GameItem::mouseDoubleClickEvent)");
	}

	if (m_controller->newHighScore(m_level, (event->y()))) {
		emit gameFinished(true);
	} else {
		emit gameFinished(false);
	}
}
