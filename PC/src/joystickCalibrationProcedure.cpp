#include "joystickCalibrationProcedure.h"
#include "controller.h"
#include "myRuntimeException.h"
#include "helpers.h"

JoystickCalibrationProcedure::JoystickCalibrationProcedure(Controller* controller, QObject* parent)
	: QObject(parent)
	, m_controller(controller)
{
}

JoystickCalibrationProcedure::~JoystickCalibrationProcedure()
{
}

void JoystickCalibrationProcedure::setJoystickCalibrationStatus(JoystickCalibrationStatus status)
{
// 	QString statusString;
// 	switch (status) {
// 		case Start:
// 			statusString = "";
// 			break;
// 		case Center:
// 			statusString = "center";
// 			break;
// 		case Up:
// 			statusString = "up";
// 			break;
// 		case Down:
// 			statusString = "down";
// 			break;
// 		case Left:
// 			statusString = "left";
// 			break;
// 		case Right:
// 			statusString = "right";
// 			break;
// 	}
//
// 	Forse aggiungere status "done" alla calibrazione qml che mostra "calibrazione finita", disabilita indietro e dopo qualche secondo torna alla schermata precedente
//
// 	// Setting the status in the joystick calibration item
// 	QQmlProperty::write(m_joystickCalibration, "state", statusString);
}
