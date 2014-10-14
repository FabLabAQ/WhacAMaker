#include "moleSpot.h"
#include <QPen>
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

// 	// The dimension of the playground. The playground is squared and takes the up left part of the display
// 	const qreal playgroundSize = (width() < height()) ? width() : height();
//
// 	// Drawing the playground with the cells for the moles
// 	const qreal playgroundPenWidth = 1.0;
// 	const QPen playgroundPen(Qt::black, playgroundPenWidth);
// 	const QBrush playgroundBrush(Qt::darkGray);
// 	painter->setPen(playgroundPen);
// 	painter->setBrush(playgroundBrush);
// 	QRectF moleCell(0.0, 0.0, (playgroundSize / 3.0) - playgroundPenWidth, (playgroundSize / 3.0) - playgroundPenWidth);
//
// 	for (int r = 0; r < 3; r++) {
// 		for (int c = 0; c < 3; c++) {
// 			moleCell.moveTo(c * moleCell.width(), r * moleCell.height());
// 			painter->drawRect(moleCell);
// 		}
// 	}
//
// 	// The rectangle size of the area in which we draw additional information
// 	const qreal infoWidth = (width() < height()) ? width() : (width() - height());
// 	const qreal infoHeight = (height() < width()) ? height() : (height() - width());
//
// 	// The position of the top left point where additional information is drawn
// 	const QPointF infoTopLeft((width() < height()) ? 0 : playgroundSize, (height() < width()) ? 0 : playgroundSize);
//
// 	// The pen used to draw text
// 	const QPen textPen(Qt::black, 1);
//
// 	// Now we have four blocks of text: level, score, remaining ammunitions, remaining time. Computing dimensions.
// 	const qreal textAreaHeight = infoHeight / 4.0;
// 	const qreal textXPos = infoWidth / 10.0;
// 	const qreal firstLineYPosInArea = textAreaHeight / 6.0;
// 	const qreal textHeight = textAreaHeight / 3.0;
//
// 	painter->setPen(textPen);
//
// 	// Printing text. Level...
// 	qreal curAreaYPos = 0.0;
// 	painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea), m_levelText);
// 	QPen levelPen = textPen;
// 	if (m_level == Easy) {
// 		levelPen.setColor(Qt::green);
// 		painter->setPen(levelPen);
// 		painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), m_easyLevelText);
// 	} else if (m_level == Medium) {
// 		levelPen.setColor(Qt::yellow);
// 		painter->setPen(levelPen);
// 		painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), m_mediumLevelText);
// 	} else {
// 		levelPen.setColor(Qt::red);
// 		painter->setPen(levelPen);
// 		painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), m_hardLevelText);
// 	}
// 	painter->setPen(textPen);
//
// 	// ... score...
// 	curAreaYPos += textAreaHeight;
// 	painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea), m_scoreText);
// 	painter->drawText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), "1234");
//
// 	// ... remaining ammo...
// 	curAreaYPos += textAreaHeight;
// 	painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea), m_ammoText);
// 	painter->drawText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), "5");
//
// 	// ... and remaining time
// 	curAreaYPos += textAreaHeight;
// 	painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea), m_timeLeftText);
// 	const int minutes = m_remainingSeconds / 60;
// 	const int seconds = m_remainingSeconds % 60;
// 	const QString r = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0'));
// 	painter->drawText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), r);

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

// // Useful constants
// namespace {
// 	/**
// 	 * \brief How many seconds the game lasts
// 	 */
// 	const int gameDuration = 120;
// }
//
// GameItem::GameItem(QQuickItem *parent)
// 	: QQuickPaintedItem(parent)
// 	, m_controller(NULL)
// 	, m_level(Easy)
// 	, m_levelText("Livello")
// 	, m_easyLevelText("Facile")
// 	, m_mediumLevelText("Medio")
// 	, m_hardLevelText("Difficile")
// 	, m_scoreText("Punteggio")
// 	, m_ammoText("Colpi rimasti")
// 	, m_timeLeftText("Tempo rimasto")
// 	, m_timer()
// 	, m_remainingSeconds(0)
// {
// 	setAcceptedMouseButtons(Qt::AllButtons);
//
// 	// Connecting timer signal
// 	connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
// }
//
// void GameItem::setController(Controller* controller)
// {
// 	m_controller = controller;
// }
//
// void GameItem::paint(QPainter *painter)
// {
// 	// Activating antialiasing
// 	painter->setRenderHints(QPainter::Antialiasing, true);
//
// 	// The dimension of the playground. The playground is squared and takes the up left part of the display
// 	const qreal playgroundSize = (width() < height()) ? width() : height();
//
// 	// Drawing the playground with the cells for the moles
// 	const qreal playgroundPenWidth = 1.0;
// 	const QPen playgroundPen(Qt::black, playgroundPenWidth);
// 	const QBrush playgroundBrush(Qt::darkGray);
// 	painter->setPen(playgroundPen);
// 	painter->setBrush(playgroundBrush);
// 	QRectF moleCell(0.0, 0.0, (playgroundSize / 3.0) - playgroundPenWidth, (playgroundSize / 3.0) - playgroundPenWidth);
//
// 	for (int r = 0; r < 3; r++) {
// 		for (int c = 0; c < 3; c++) {
// 			moleCell.moveTo(c * moleCell.width(), r * moleCell.height());
// 			painter->drawRect(moleCell);
// 		}
// 	}
//
// 	// The rectangle size of the area in which we draw additional information
// 	const qreal infoWidth = (width() < height()) ? width() : (width() - height());
// 	const qreal infoHeight = (height() < width()) ? height() : (height() - width());
//
// 	// The position of the top left point where additional information is drawn
// 	const QPointF infoTopLeft((width() < height()) ? 0 : playgroundSize, (height() < width()) ? 0 : playgroundSize);
//
// 	// The pen used to draw text
// 	const QPen textPen(Qt::black, 1);
//
// 	// Now we have four blocks of text: level, score, remaining ammunitions, remaining time. Computing dimensions.
// 	const qreal textAreaHeight = infoHeight / 4.0;
// 	const qreal textXPos = infoWidth / 10.0;
// 	const qreal firstLineYPosInArea = textAreaHeight / 6.0;
// 	const qreal textHeight = textAreaHeight / 3.0;
//
// 	painter->setPen(textPen);
//
// 	// Printing text. Level...
// 	qreal curAreaYPos = 0.0;
// 	painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea), m_levelText);
// 	QPen levelPen = textPen;
// 	if (m_level == Easy) {
// 		levelPen.setColor(Qt::green);
// 		painter->setPen(levelPen);
// 		painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), m_easyLevelText);
// 	} else if (m_level == Medium) {
// 		levelPen.setColor(Qt::yellow);
// 		painter->setPen(levelPen);
// 		painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), m_mediumLevelText);
// 	} else {
// 		levelPen.setColor(Qt::red);
// 		painter->setPen(levelPen);
// 		painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), m_hardLevelText);
// 	}
// 	painter->setPen(textPen);
//
// 	// ... score...
// 	curAreaYPos += textAreaHeight;
// 	painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea), m_scoreText);
// 	painter->drawText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), "1234");
//
// 	// ... remaining ammo...
// 	curAreaYPos += textAreaHeight;
// 	painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea), m_ammoText);
// 	painter->drawText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), "5");
//
// 	// ... and remaining time
// 	curAreaYPos += textAreaHeight;
// 	painter->drawStaticText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea), m_timeLeftText);
// 	const int minutes = m_remainingSeconds / 60;
// 	const int seconds = m_remainingSeconds % 60;
// 	const QString r = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0'));
// 	painter->drawText(infoTopLeft + QPointF(textXPos, curAreaYPos + firstLineYPosInArea + textHeight), r);
// }
//
// void GameItem::setDifficultyLevel(DifficultyLevel newLevel)
// {
// 	if (newLevel != m_level) {
// 		m_level = newLevel;
// 		update();
// 		emit difficultyLevelChanged();
// 	}
// }
//
// void GameItem::startGame()
// {
// 	m_remainingSeconds = gameDuration;
// 	m_timer.start(1000);
//
// 	update();
// }
//
// void GameItem::mouseDoubleClickEvent(QMouseEvent *event)
// {
// 	if (m_controller == NULL) {
// 		throwMyRuntimeException("Controller not set in GameItem (in GameItem::mouseDoubleClickEvent)");
// 	}
//
// 	if (m_controller->newHighScore(m_level, (event->y()))) {
// 		emit gameFinished(true);
// 	} else {
// 		emit gameFinished(false);
// 	}
// }
//
// void GameItem::timeout()
// {
// 	m_remainingSeconds--;
//
// 	if (m_remainingSeconds == 0) {
// 		m_timer.stop();
//
// 		emit gameFinished(false);
// 	}
//
// 	update();
// }
