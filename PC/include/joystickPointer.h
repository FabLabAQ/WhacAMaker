#ifndef __JOYSTICK_POINTER_H__
#define __JOYSTICK_POINTER_H__

#include <QObject>
#include <QQuickView>
#include <QRectF>
#include <QTime>

class Controller;

/**
 * \brief The object managing the joystick pointer
 *
 * This received joystick positions from the controller and directly interact
 * with the joystickPointer QML object. This class has two signals which are
 * emitted at the same time whenever a new joystick position is received. The
 * difference is that the absolute position they have as parameters, is computed
 * differently:
 * 	- joystickMovedRelative computes the position as a relative movement of
 * 	  the joystick, e.g. if the joystick is up, the pointer is moved upward
 * 	  from his current position
 * 	- joystickMovedAbsolute computes the position as an absolute movement of
 * 	  the joystick, e.g. is the joystick is up, the pointer is moved in the
 * 	  up position in the screen, always at the same position regardles of
 * 	  the pointer previous position
 */
class JoystickPointer : public QObject
{
	Q_OBJECT

public:
	/**
	 * \brief Possible states for the pointer
	 */
	enum States {
		Normal,
		Game,
		Calibration
	};

	/**
	 * \brief Possible movement types for the pointer
	 */
	enum MovementType {
		Relative,
		Absolute
	};

public:
	/**
	 * \brief Constructor
	 *
	 * \param controller the application controller object
	 * \param view the QML viewer, passed here to get the pointer to the QML
	 *             joystick pointer
	 * \param parent the parent QObject
	 */
	JoystickPointer(Controller* controller, QQuickView& view, QObject* parent = NULL);

	/**
	 * \brief Destructor
	 */
	virtual ~JoystickPointer();

	/**
	 * \brief The joystick commands as received from Arduino
	 *
	 * \param xPosition the position of the X axis in range [0, 1023]
	 * \param yPosition the position of the Y axis in range [0, 1023]
	 * \param button1Pressed whether the button 1 has been pressed or not
	 * \param button2Pressed whether the button 2 has been pressed or not
	 */
	void joystickCommands(int xPosition, int yPosition, bool button1Pressed, bool button2Pressed);

	/**
	 * \brief Changes the status of the joystick pointer
	 *
	 * \param newState the new state of the joystick pointer
	 */
	void setStatus(States newState);

	/**
	 * \brief Returns the current status of the joystick pointer
	 *
	 * \return the current status of the joystick pointer
	 */
	States status() const;

	/**
	 * \brief Changes the type of movement of the joystick pointer
	 *
	 * \param t the type of movement
	 */
	void setMovementType(MovementType t);

	/**
	 * \brief Returns the type of movement of the joystick pointer
	 *
	 * \return the type of movement of the joystick pointer
	 */
	MovementType movementType() const;

	/**
	 * \brief Sets the movement area of the joystick pointer
	 *
	 * \param rect the movement area. If it is invalid, the whole qml view
	 *             area is used
	 */
	void setMovementArea(const QRectF& rect = QRectF());

	/**
	 * \brief Returns the movement area of the joystick pointer
	 *
	 * \return the movement area of the joystick pointer
	 */
	const QRectF& movementArea() const;
signals:
	/**
	 * \brief The signal emitted whenever the joystick is moved with the
	 *        position resulting from a relative movement
	 *
	 * See class description for more information
	 * \param x the x position of the pointer on the main view frame of
	 *          reference
	 * \param y the y position of the pointer on the main view frame of
	 *          reference
	 * \param button1Pressed whether the first button is pressed or not
	 * \param button2Pressed whether the second button is pressed or not
	 */
	void joystickMovedRelative(qreal x, qreal y, bool button1Pressed, bool button2Pressed);

	/**
	 * \brief The signal emitted whenever the joystick is moved with the
	 *        position resulting from a absolute movement
	 *
	 * See class description for more information
	 * \param x the x position of the pointer on the main view frame of
	 *          reference
	 * \param y the y position of the pointer on the main view frame of
	 *          reference
	 * \param button1Pressed whether the first button is pressed or not
	 * \param button2Pressed whether the second button is pressed or not
	 */
	void joystickMovedAbsolute(qreal x, qreal y, bool button1Pressed, bool button2Pressed);

private:
	/**
	 * \brief The application controller object
	 */
	Controller* const m_controller;

	/**
	 * \brief The QML joystick pointer object
	 */
	QObject* const m_qmlJoystickPointer;

	/**
	 * \brief The movement type for the pointer
	 */
	MovementType m_movementType;

	/**
	 * \brief The rectange inside which the pointer should move
	 *
	 * By default the whole view
	 */
	QRectF m_movementArea;

	/**
	 * \brief The object to measure time passed since the last pointer
	 *        movement
	 */
	QTime m_movementTime;
};

#endif

