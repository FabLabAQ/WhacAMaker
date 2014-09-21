#include "joystickPointer.h"
#include "controller.h"
#include "myRuntimeException.h"
#include "helpers.h"
#include <QQmlProperty>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QPointF>

JoystickPointer::JoystickPointer(Controller* controller, QQuickView& view, QObject* parent)
	: QObject(parent)
	, m_controller(controller)
	, m_qmlJoystickPointer(getQmlObject(view, "joystickPointerObject"))
	, m_button1PrevStatus(false)
	, m_button2PrevStatus(false)
{
	// Putting the joystick in the central part of the window
	QQmlProperty::write(m_qmlJoystickPointer, "x", view.width() / 2);
	QQmlProperty::write(m_qmlJoystickPointer, "y", view.height() / 2);
}

JoystickPointer::~JoystickPointer()
{
	// Nothing to do here
}

void JoystickPointer::joystickCommands(int xPosition, int yPosition, bool button1Pressed, bool button2Pressed)
{
#warning TODO, METTERE PARAMETRI NEL FILE DI CONFIGURAZIONE PER JOYSTICK, LEGARE VELOCITÀ A POSIZIONI ASSI (usare timer per calcolare spostamento in pixel) E ANIMARE IL CLICK
	// Computing the displacement depending on the axes positions
	double deltaX = 0.0;
	if (xPosition < 312) {
		deltaX += 10;
	} else if (xPosition > 712) {
		deltaX -= 10;
	}
	double deltaY = 0.0;
	if (yPosition < 312) {
		deltaY += 10;
	} else if (yPosition > 712) {
		deltaY -= 10;
	}

	// Getting the current pointer position and moving it
	const double curX = QQmlProperty::read(m_qmlJoystickPointer, "x").toDouble();
	const double curY = QQmlProperty::read(m_qmlJoystickPointer, "y").toDouble();
	double newX = curX + deltaX;
	double newY = curY + deltaY;

	if ((newX > 0.0) && (newX < m_controller->view().width())) {
		QQmlProperty::write(m_qmlJoystickPointer, "x", newX);
	} else {
		newX = curX;
	}
	if ((newY > 0.0) && (newY < m_controller->view().height())) {
		QQmlProperty::write(m_qmlJoystickPointer, "y", newY);
	} else {
		newY = curY;
	}

	// Checking if we have to send a click signal. For the moment we only use button1
	if (m_button1PrevStatus != button1Pressed) {
		if (button1Pressed) {
			// Send mouse button pressed
			QMouseEvent* pressEvent = new QMouseEvent(QEvent::MouseButtonPress, QPointF(newX, newY), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
			QGuiApplication::sendEvent(&(m_controller->view()), pressEvent);
		} else {
			// Send mouse button released
			QMouseEvent* releaseEvent = new QMouseEvent(QEvent::MouseButtonRelease, QPointF(newX, newY), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
			QGuiApplication::sendEvent(&(m_controller->view()), releaseEvent);
		}
	}

	// Saving the status of buttons
	m_button1PrevStatus = button1Pressed;
	m_button2PrevStatus = button2Pressed;
}

void JoystickPointer::setStatus(States newState)
{
	QString statusString;
	switch (newState) {
		case Normal:
			statusString = "";
			break;
		case Game:
			statusString = "game";
			break;
		case Calibration:
			statusString = "calibration";
			break;
	}

	// Setting the status in the joystick pointer item
	QQmlProperty::write(m_qmlJoystickPointer, "state", statusString);
}

JoystickPointer::States JoystickPointer::status() const
{
	// Getting the status from the joystick pointer item
	QString statusString = QQmlProperty::read(m_qmlJoystickPointer, "state").toString();

	States curState = Normal;
	if (statusString == "game") {
		curState = Game;
	} else if (statusString == "calibration") {
		curState = Calibration;
	}

	return curState;
}

