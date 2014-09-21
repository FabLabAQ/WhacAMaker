#ifndef __JOYSTICK_POINTER_H__
#define __JOYSTICK_POINTER_H__

#include <QObject>
#include <QQuickView>

class Controller;

/**
 * \brief The object managing the joystick pointer
 *
 * This received joystick positions from the controller and directly interact
 * with the joystickPointer QML object
 */
class JoystickPointer : public QObject
{
	Q_OBJECT

	enum States {
		Normal,
		Game,
		Calibration
	};

public:
	/**
	 * \brief Constructor
	 *
	 * \param controller the application controller object
	 * \param view the QML viewer, passed here to get the pointer to the QML
	 *             joystick pointer
	 */
	JoystickPointer(Controller* controller, QQuickView& view, QObject* parent = NULL);

	/**
	 * \brief Destructor
	 */
	~JoystickPointer();

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
	 * \param the new state of the joystick pointer
	 */
	void setStatus(States newState);

	/**
	 * \brief Returns the current status of the joystick pointer
	 *
	 * \return the current status of the joystick pointer
	 */
	States status() const;

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
	 * \brief The previous status of button 1 (whether pressed or not)
	 */
	bool m_button1PrevStatus;

	/**
	 * \brief The previous status of button 2 (whether pressed or not)
	 */
	bool m_button2PrevStatus;
};

#endif

