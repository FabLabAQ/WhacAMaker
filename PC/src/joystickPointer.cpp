#include "joystickPointer.h"
#include "controller.h"
#include "myRuntimeException.h"
#include "helpers.h"
#include <QQmlProperty>
#include <QMouseEvent>
#include <QPointF>

namespace {
	// Useful constants
	const qreal pointerMaxVel = 300.0; // pixels/sec
	const int noMovementHRange = 100;
	const int lowLimitNoMov = 512 - noMovementHRange;
	const int highLimitNoMov = 512 + noMovementHRange;
}

JoystickPointer::JoystickPointer(Controller* controller, QQuickView& view, QObject* parent)
	: QObject(parent)
	, m_controller(controller)
	, m_qmlJoystickPointer(getQmlObject(view, "joystickPointerObject"))
	, m_movementType(Relative)
	, m_movementArea(0.0, 0.0, view.width(), view.height())
	, m_movementTime()
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
	// Computing the displacement depending on the axes positions. If this is the first command we
	// receive, we set delta to 0
	qreal deltaX = 0.0;
	qreal deltaY = 0.0;

	if (m_movementTime.isValid()) {
		const int msec = m_movementTime.restart();

		qreal v = 0.0;
		if (xPosition < lowLimitNoMov) {
			v = (qreal(lowLimitNoMov - xPosition) / qreal(lowLimitNoMov)) * pointerMaxVel;
		} else if (xPosition > highLimitNoMov) {
			v = -(qreal(xPosition - highLimitNoMov) / qreal(lowLimitNoMov)) * pointerMaxVel;
		}
		deltaX += v * qreal(msec) / 1000.0;

		//std::cerr << "xPosition: " << xPosition << ", lowLimitNoMov: " << lowLimitNoMov << ", highLimitNoMov: " << highLimitNoMov << ", v: " << v << ", deltaX: " << deltaX << std::endl;

		v = 0.0;
		if (yPosition < lowLimitNoMov) {
			v = (qreal(lowLimitNoMov - yPosition) / qreal(lowLimitNoMov)) * pointerMaxVel;
		} else if (yPosition > highLimitNoMov) {
			v = -(qreal(yPosition - highLimitNoMov) / qreal(lowLimitNoMov)) * pointerMaxVel;
		}
		deltaY += v * qreal(msec) / 1000.0;
	} else {
		m_movementTime.start();
	}

	// Getting the current pointer position and computing the new relative movement position
	const qreal curX = QQmlProperty::read(m_qmlJoystickPointer, "x").toDouble();
	const qreal curY = QQmlProperty::read(m_qmlJoystickPointer, "y").toDouble();
	qreal newRelX = curX + deltaX;
	qreal newRelY = curY + deltaY;

	if (newRelX < m_movementArea.left()) {
		newRelX = m_movementArea.left();
	} else if (newRelX > m_movementArea.right()) {
		newRelX = m_movementArea.right();
	}
	if (newRelY < m_movementArea.top()) {
		newRelY = m_movementArea.top();
	} else if (newRelY > m_movementArea.bottom()) {
		newRelY = m_movementArea.bottom();
	}

	// Sending the new relative movement position
	emit joystickMovedRelative(newRelX, newRelY, button1Pressed, button2Pressed);

	// Now computing the new absolute position and sending it
	const qreal newAbsX = (1.0 - (xPosition / 1023.0)) * m_movementArea.width() + m_movementArea.left();
	const qreal newAbsY = (1.0 - (yPosition / 1023.0)) * m_movementArea.height() + m_movementArea.top();
	emit joystickMovedAbsolute(newAbsX, newAbsY, button1Pressed, button2Pressed);

	// Moving the pointer, depending on the type of movement
	if (m_movementType == Relative) {
		QQmlProperty::write(m_qmlJoystickPointer, "x", newRelX);
		QQmlProperty::write(m_qmlJoystickPointer, "y", newRelY);
	} else {
		QQmlProperty::write(m_qmlJoystickPointer, "x", newAbsX);
		QQmlProperty::write(m_qmlJoystickPointer, "y", newAbsY);
	}

	// Also telling the qml pointer the status of buttons
	const QVariant vb1 = button1Pressed;
	const QVariant vb2 = button2Pressed;
	QMetaObject::invokeMethod(m_qmlJoystickPointer, "joystickButtonStates", Q_ARG(QVariant, vb1), Q_ARG(QVariant, vb2));
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

void JoystickPointer::setMovementType(MovementType t)
{
	m_movementType = t;
}

JoystickPointer::MovementType JoystickPointer::movementType() const
{
	return m_movementType;
}

void JoystickPointer::setMovementArea(const QRectF& rect)
{
	if (!rect.isValid()) {
		m_movementArea = QRectF(0.0, 0.0, m_controller->view().width(), m_controller->view().height());
	} else {
		m_movementArea = rect;
	}
}

const QRectF& JoystickPointer::movementArea() const
{
	return m_movementArea;
}
