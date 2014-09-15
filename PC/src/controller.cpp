#include "controller.h"
#include <QQuickItem>
#include <QMetaObject>
#include <QQmlProperty>
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

	// Restoring all highscores
	restoreHighScores(GameItem::Easy);
	restoreHighScores(GameItem::Medium);
	restoreHighScores(GameItem::Hard);

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

	// First of all getting the list of highscores for the level
	QList<QVariant> highscores;
	QList<QVariant> players;
	QString levelName;
	getHighScoresFromSettings(m_nextScoreLevel, highscores, players, levelName);

	// Just a safety check
	if (highscores.size() != players.size()) {
		throwMyRuntimeException("The list of scores is different from the list of players!!!");
	}

	// Now checking where the new highscore goes
	int scoreAdded = false;
	for (int i = 0; (i < highscores.size()) && (!scoreAdded); i++) {
		if (m_nextScore > highscores[i].toDouble()) {
			highscores.insert(i, m_nextScore);
			players.insert(i, name);

			scoreAdded = true;
		}
	}

	if (!scoreAdded) {
		// Adding at the end of the list
		highscores.append(m_nextScore);
		players.append(name);
	}

	// Now removing scores in excess
	while (highscores.size() > numHighscores) {
		highscores.removeLast();
	}
	while (players.size() > numHighscores) {
		players.removeLast();
	}

	// Saving lists
	m_settings.setValue("highscores/" + levelName + "Scores", highscores);
	m_settings.setValue("highscores/" + levelName + "Players", players);

	// Now changing lists in the qml item
	restoreHighScores(m_nextScoreLevel);
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

void Controller::restoreHighScores(GameItem::DifficultyLevel level)
{
	// First of all getting the list of highscores for the level
	QList<QVariant> highscores;
	QList<QVariant> players;
	QString levelName;
	getHighScoresFromSettings(level, highscores, players, levelName);

	// Now getting the object whose highscores we have to restore
	const QString methodName = levelName.toLower() + "ScoreObject";
	QVariant returnedObject;
	QMetaObject::invokeMethod(m_view.rootObject(), methodName.toLatin1().data(), Q_RETURN_ARG(QVariant, returnedObject));
	QObject* const scoreItem = qvariant_cast<QObject *>(returnedObject);

	if (scoreItem == NULL) {
		throwMyRuntimeException("Cannot access the score object with the " + methodName + " qml method");
	}

	// Now setting the properties
	QQmlProperty::write(scoreItem, "playersNames", players);
	QQmlProperty::write(scoreItem, "playersScores", highscores);
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

void Controller::getHighScoresFromSettings(GameItem::DifficultyLevel level, QList<QVariant>& highscores, QList<QVariant>& players, QString& levelName)
{
	if (level == GameItem::Easy) {
		levelName = "Easy";
	} else if (level == GameItem::Medium) {
		levelName = "Medium";
	} else if (level == GameItem::Hard) {
		levelName = "Hard";
	}
	highscores = m_settings.value("highscores/" + levelName + "Scores").toList();
	players = m_settings.value("highscores/" + levelName + "Players").toList();
}
