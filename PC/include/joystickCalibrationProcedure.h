#ifndef __JOYSTICK_CALIBRATION_PROCEDURE_H__
#define __JOYSTICK_CALIBRATION_PROCEDURE_H__

#include <QObject>
#include <QQuickView>

class Controller;

/**
 * \brief The object taking care of the joystick calibration procedure
 *
 * This received joystick positions from the controller and directly interact
 * with the joystickCalibration QML object
 */
class JoystickCalibrationProcedure : public QObject
{
	Q_OBJECT

	/**
	 * \brief The joystick calibration status
	 */
	enum JoystickCalibrationStatus {
		Started,
		Center,
		Done
	};

public:
	/**
	 * \brief Constructor
	 *
	 * \param controller the application controller object
	 */
	JoystickCalibrationProcedure(Controller* controller, QObject* parent = NULL);

	/**
	 * \brief Destructor
	 */
	~JoystickCalibrationProcedure();

private slots:

	/**
	 * \brief The slot called to set the current joystick calibration status
	 */
	void setJoystickCalibrationStatus(JoystickCalibrationStatus status);

private:
	/**
	 * \brief The application controller object
	 */
	Controller* const m_controller;
};

#endif

