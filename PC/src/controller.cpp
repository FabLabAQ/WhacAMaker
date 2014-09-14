#include "controller.h"
#include <QQuickItem>
#include <QMetaObject>
#include <QVariant>
#include <QQmlProperty>
#include <QList>
#include "myRuntimeException.h"

namespace {
	// Some constants
	const int numHighscores = 7;
}

Controller::Controller(QQuickView& view, QObject* parent) :
	QObject(parent),
	m_settings(),
	m_view(view),
	m_nextScoreLevel(GameItem::Easy),
	m_nextScore(0.0)
{
	// Setting ourself as the controller in the game object
	qmlGameObject()->setController(this);

	// Restores settings in the configuration parameters QML object
	restoreParameters();

	// Connecting signals from m_view to our slots
	connect(m_view.rootObject(), SIGNAL(configurationParametersSaved()), this, SLOT(saveConfigurationParameters()));
	connect(m_view.rootObject(), SIGNAL(playerNameEntered(QString)), this, SLOT(savePlayerName(QString)));
}

Controller::~Controller()
{
	// Nothing to do here
}

bool Controller::newHighScore(GameItem::DifficultyLevel level, double score)
{
	// First of all getting the list of highscores for the level
	QString paramName = "";
	if (level == GameItem::Easy) {
		paramName = "EasyScores";
	} else if (level == GameItem::Medium) {
		paramName = "MediumScores";
	} else if (level == GameItem::Hard) {
		paramName = "HardScores";
	}
	const QList<QVariant> highscores = m_settings.value("highscores/" + paramName).toList();

	// Now checking if the score is higher than the last score
	if ((highscores.isEmpty()) || (score > highscores.last().toDouble())) {
		m_nextScoreLevel = level;
		m_nextScore = score;

		return true;
	}

	return false;
}

void Controller::saveConfigurationParameters()
{
	// Getting a reference to the QML object string the parameters
	QObject* const configurationItem = qmlConfigurationParametersObject();

	// Saving to the configuration object
	copyPropertyToSettings(configurationItem, "serialPort");
	copyPropertyToSettings(configurationItem, "screenDistance");
	copyPropertyToSettings(configurationItem, "verticalScreenCenterDistance");
	copyPropertyToSettings(configurationItem, "horizontalScreenCenterDistance");
}

void Controller::savePlayerName(const QString& name)
{
	// If we get here it means that we have to save a new highscore
	ghdfghdfghdfgh
}

void Controller::restoreParameters()
{
	// Getting a reference to the QML object string the parameters
	QObject* const configurationItem = qmlConfigurationParametersObject();

	// Storing settings inside the configurationItem
	copyPropertyToItem(configurationItem, "serialPort");
	copyPropertyToItem(configurationItem, "screenDistance");
	copyPropertyToItem(configurationItem, "verticalScreenCenterDistance");
	copyPropertyToItem(configurationItem, "horizontalScreenCenterDistance");
}

QObject* Controller::qmlConfigurationParametersObject()
{
	// Getting a reference to the QML object string the parameters
	QVariant returnedObject;
	QMetaObject::invokeMethod(m_view.rootObject(), "configurationParametersObject", Q_RETURN_ARG(QVariant, returnedObject));
	QObject* const configurationItem = qvariant_cast<QObject *>(returnedObject);

	if (configurationItem == NULL) {
		throwMyRuntimeException("Cannot access the configuration parameters object");
	}

	return configurationItem;
}

GameItem* Controller::qmlGameObject()
{
	// Getting a reference to the QML object string the parameters
	QVariant returnedObject;
	QMetaObject::invokeMethod(m_view.rootObject(), "gameObject", Q_RETURN_ARG(QVariant, returnedObject));
	GameItem* const gameItem = qvariant_cast<GameItem *>(returnedObject);

	if (gameItem == NULL) {
		throwMyRuntimeException("Cannot access the game object");
	}

	return gameItem;
}

void Controller::copyPropertyToItem(QObject* item, QString propName)
{
	QQmlProperty::write(item, propName + "Value", m_settings.value("configuration/" + propName));
}

void Controller::copyPropertyToSettings(QObject* item, QString propName)
{
	if (QQmlProperty::read(item, propName + "Acceptable").toBool()) {
		m_settings.setValue("configuration/" + propName, QQmlProperty::read(item, propName + "Value"));
	} else {
		copyPropertyToItem(item, propName);
	}
}
