#include "controller.h"
#include <QQuickItem>
#include <QMetaObject>
#include <QQmlProperty>
#include <QGuiApplication>
#include <QTest>
#include "myRuntimeException.h"
#include "helpers.h"
#include <iostream>
#include <cmath>

namespace {
	// Some constants
	const int numHighscores = 7;
}

Controller::Controller(QQuickView& view, QObject* parent)
	: QObject(parent)
	, m_status(Menu)
	, m_settings()
	, m_view(view)
	, m_serialCom(this)
	, m_joystickPointer(this, view)
	, m_gameController(this, &m_joystickPointer, &m_serialCom, view)
	, m_nextScoreLevel(WhackAMaker::Easy)
	, m_nextScore(0.0)
	, m_joystickPrevX(0.0)
	, m_joystickPrevY(0.0)
	, m_button1PrevStatus(false)
	, m_button2PrevStatus(false)
{
	// Restores settings in the configuration parameters QML object
	restoreParameters();

	// Sets the port in the serial comunication
	setSerialPort();

	// Restoring all highscores
	restoreHighScores(WhackAMaker::Easy);
	restoreHighScores(WhackAMaker::Medium);
	restoreHighScores(WhackAMaker::Hard);

	// Initially setting the movement type of the pointer to relative
	m_joystickPointer.setMovementType(JoystickPointer::Relative);

	// Connecting signals from m_view to our slot to be notified of dimension changes
	connect(&m_view, SIGNAL(widthChanged(int)), this, SLOT(resizeJoystickMovementArea()));
	connect(&m_view, SIGNAL(heightChanged(int)), this, SLOT(resizeJoystickMovementArea()));

	// Connecting signals from qml root object to our slots
	connect(m_view.rootObject(), SIGNAL(configurationParametersSaved()), this, SLOT(saveConfigurationParameters()));
	connect(m_view.rootObject(), SIGNAL(playerNameEntered(QString)), this, SLOT(savePlayerName(QString)));
	connect(m_view.rootObject(), SIGNAL(joystickCalibrationStarted()), this, SLOT(joystickCalibrationStarted()));
	connect(m_view.rootObject(), SIGNAL(joystickCalibrationEnded()), this, SLOT(joystickCalibrationEnded()));
	connect(m_view.rootObject(), SIGNAL(gameStarted()), this, SLOT(gameStarted()));
	connect(m_view.rootObject(), SIGNAL(gameFinished()), this, SLOT(gameFinished()));

	// Connecting the joystick relative movement signal from the joystick pointer to our slot
	connect(&m_joystickPointer, SIGNAL(joystickMovedRelative(qreal, qreal, bool, bool)), this, SLOT(pointerPosition(qreal, qreal, bool, bool)));

	// Telling the controller to start sending joystick data. We send two times because the first one there could
	// be garbage
	m_serialCom.newCommandToSend();
	m_serialCom.appendCommandPart("S");
	m_serialCom.sendCommand();
	m_serialCom.newCommandToSend();
	m_serialCom.appendCommandPart("S");
	m_serialCom.sendCommand();
}

Controller::~Controller()
{
	// Nothing to do here
}

bool Controller::newHighScore(WhackAMaker::DifficultyLevel level, double score)
{
	// First of all getting the list of highscores for the level
	QString paramName = "";
	if (level == WhackAMaker::Easy) {
		paramName = "EasyScores";
	} else if (level == WhackAMaker::Medium) {
		paramName = "MediumScores";
	} else if (level == WhackAMaker::Hard) {
		paramName = "HardScores";
	}
	const QList<QVariant> highscores = m_settings.value("highscores/" + paramName).toList();

	// Now checking if the score is higher than the last score
	if ((highscores.size() < numHighscores) || (score > highscores.last().toDouble())) {
		m_nextScoreLevel = level;
		m_nextScore = score;

		return true;
	} else {
		m_nextScore = -1.0;

		return false;
	}
}

void Controller::commandReceived()
{
	if ((!m_serialCom.extractReceivedCommand()) || (m_serialCom.receivedCommandNumParts() == 0)) {
		throwMyRuntimeException("Internal error: command received but m_serialCom.extractReceivedCommand() returned false");
	}

	if (m_serialCom.receivedCommandPart(0) == "J") {
		if (m_serialCom.receivedCommandNumParts() != 5) {
			QString command = m_serialCom.receivedCommandPart(0);
			for (int i = 1; i < m_serialCom.receivedCommandNumParts(); ++i) {
				command += " " + m_serialCom.receivedCommandPart(i);
			}

			// Ignoring command, but not throwing an exception
			std::cerr << "Invalid Joystick command (" << command.toLatin1().data() << ")!!!" << std::endl;
		} else {
			m_joystickPointer.joystickCommands(m_serialCom.receivedCommandPartAsInt(1), m_serialCom.receivedCommandPartAsInt(2), m_serialCom.receivedCommandPartAsInt(3), m_serialCom.receivedCommandPartAsInt(4));
		}
	}
}

void Controller::saveConfigurationParameters()
{
	// Getting a reference to the QML object string the parameters
	QObject* const configurationItem = getQmlObject(m_view, "configurationParametersObject");

	// Saving to the configuration object
	if (copyPropertyToSettings(configurationItem, "serialPort")) {
		// Also setting the serial port in the serial communication object
		setSerialPort();
	}
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

void Controller::joystickCalibrationStarted()
{
	m_status = JoystickCalibration;

	// Changing pointer status and movement type
	m_joystickPointer.setStatus(JoystickPointer::Calibration);
	m_joystickPointer.setMovementType(JoystickPointer::Absolute);
	resizeJoystickMovementArea();
}

void Controller::joystickCalibrationEnded()
{
	m_status = Menu;

	// Changing pointer status and movement type
	m_joystickPointer.setStatus(JoystickPointer::Normal);
	m_joystickPointer.setMovementType(JoystickPointer::Relative);
	resizeJoystickMovementArea();
}

void Controller::pointerPosition(qreal x, qreal y, bool button1Pressed, bool button2Pressed)
{
	// Checking status, we only do things in menu and calibration status
	if ((m_status != Menu) && (m_status != JoystickCalibration)) {
		return;
	}

	// Simulating a mouse click. We use the Qt Test framework (perhaps it was not thought for this but it workd)
	if (m_button1PrevStatus || m_button2PrevStatus) {
		if (!button1Pressed && !button2Pressed) {
			// Send mouse click released
			QTest::mouseClick(&m_view, Qt::LeftButton, Qt::NoModifier, QPoint(x, y));
		}
	}

	// Saving the status of buttons and position of pointer
	m_joystickPrevX = x;
	m_joystickPrevY = y;
	m_button1PrevStatus = button1Pressed;
	m_button2PrevStatus = button2Pressed;
}

void Controller::gameStarted()
{
	m_status = Game;

	m_gameController.startGame();
}

void Controller::gameFinished()
{
	m_status = Menu;

	// Changing pointer status and movement type
	m_joystickPointer.setStatus(JoystickPointer::Normal);
	m_joystickPointer.setMovementType(JoystickPointer::Relative);
	resizeJoystickMovementArea();
}

void Controller::resizeJoystickMovementArea()
{
	m_joystickPointer.setMovementArea();
}

void Controller::restoreParameters()
{
	// Getting a reference to the QML object string the parameters
	QObject* const configurationItem = getQmlObject(m_view, "configurationParametersObject");

	// Storing settings inside the configurationItem
	copyPropertyToItem(configurationItem, "serialPort");
}

void Controller::restoreHighScores(WhackAMaker::DifficultyLevel level)
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

void Controller::copyPropertyToItem(QObject* item, QString propName)
{
	QQmlProperty::write(item, propName + "Value", m_settings.value("configuration/" + propName));
}

bool Controller::copyPropertyToSettings(QObject* item, QString propName)
{
	if (QQmlProperty::read(item, propName + "Acceptable").toBool()) {
		m_settings.setValue("configuration/" + propName, QQmlProperty::read(item, propName + "Value"));

		return true;
	} else {
		copyPropertyToItem(item, propName);

		return false;
	}
}

void Controller::getHighScoresFromSettings(WhackAMaker::DifficultyLevel level, QList<QVariant>& highscores, QList<QVariant>& players, QString& levelName)
{
	levelName = WhackAMaker::difficultyLevelToString(level);
	highscores = m_settings.value("highscores/" + levelName + "Scores").toList();
	players = m_settings.value("highscores/" + levelName + "Players").toList();
}

void Controller::setSerialPort()
{
	m_serialCom.setSerialPort(m_settings.value("configuration/serialPort").toString());
}
