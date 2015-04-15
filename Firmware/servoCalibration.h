#ifndef __SERVO_CALIBRATION_H__
#define __SERVO_CALIBRATION_H__

#include <Arduino.h>
#include "moles.h"
#include "serialCommunication.h"

/**
 * \brief The class to perform calibration of servos
 *
 * This class can be used to perform servo calibration. It executes in its own
 * loop, which is started in the main loop() function. While executing the
 * calibration loop, no other action can be executed. Commands available during
 * calibration are the following:
 * 	- M \<S\> \<V\> moves the servo S to value V
 * 	- L \<S\> \<V\> sets the lower value for servo S to value V
 * 	- H \<S\> \<V\> sets the upper value for servo S to value V
 * 	- P prints the current low and up limit for all servos (one line with
 * 	  the low limits separated by spaces and one line for the high limits
 * 	  separated by spaces)
 * 	- X exit the calibration procedure
 * Servos are identified by a value S that must be beween 0 and (N-1) (where N
 * is the template parameter, see below). The value giving the servo position V
 * is passed as-is to the Servo::writeMicroseconds (it should be between 700 and
 * 2300).
 *
 * The template parameter N is the number of servos to calibrate (this should be
 * equal to the number of moles, see that class documentataion for more
 * information on connections and limits).
 */
template <unsigned int N>
class ServoCalibration
{
public:
	/**
	 * \brief Constructor
	 */
	ServoCalibration();

	/**
	 * \brief Starts the calibration loop
	 *
	 * This function does not retunrn until the user sends the 'X' command.
	 * We need a Moles object to control the servos and a
	 * SerialCommunication to handle serial communication
	 * \param moles the object controlling servos
	 * \param serialCommunication the object controlling serial
	 *                            communication
	 */
	void enterLoop(Moles<N>& moles, SerialCommunication& serialCommunication);

	/**
	 * \brief Returns the vector with low limits for the servo
	 *
	 * \returns the vector with low limits for the servo
	 */
	const int* servoMin() const
	{
		return m_servoMin;
	}

	/**
	 * \brief Returns the vector with high limits for the servo
	 *
	 * \returns the vector with high limits for the servo
	 */
	const int* servoMax() const
	{
		return m_servoMax;
	}

private:
	/**
	 * \brief The minimum value for servos
	 */
	int m_servoMin[N];

	/**
	 * \brief The maxumum value for servos
	 */
	int m_servoMax[N];
};

// Template implementation of all methods

template <unsigned int N>
ServoCalibration<N>::ServoCalibration()
{
	// Initializing limits to null values
	for (int i = 0; i < N; i++) {
		m_servoMin[i] = 1500;
		m_servoMax[i] = 1500;
	}
}

template <unsigned int N>
void ServoCalibration<N>::enterLoop(Moles<N>& moles, SerialCommunication& serialCommunication)
{
	// Moving all servos to a midpoint
	for (int i = 0; i < N; ++i) {
		moles.setServoPositionRaw(i, 1500);
	}

	while (true) {
		// Reading from the serial line
		if (serialCommunication.commandReceived() && (serialCommunication.receivedCommandNumParts() != 0)) {
			if ((serialCommunication.receivedCommandPart(0)[0] == 'M')  && (serialCommunication.receivedCommandNumParts() >= 3)) {
				// Moving the servo
				moles.setServoPositionRaw(serialCommunication.receivedCommandPartAsInt(1), serialCommunication.receivedCommandPartAsInt(2));
			} else if ((serialCommunication.receivedCommandPart(0)[0] == 'L')  && (serialCommunication.receivedCommandNumParts() >= 3)) {
				// Checking the servo is valid and saving the low limit
				const int servoNum = serialCommunication.receivedCommandPartAsInt(1);

				if ((servoNum >= 0) && (servoNum < N)) {
					m_servoMin[servoNum] = serialCommunication.receivedCommandPartAsInt(2);
				}
			} else if ((serialCommunication.receivedCommandPart(0)[0] == 'H')  && (serialCommunication.receivedCommandNumParts() >= 3)) {
				// Checking the servo is valid and saving the high limit
				const int servoNum = serialCommunication.receivedCommandPartAsInt(1);

				if ((servoNum >= 0) && (servoNum < N)) {
					m_servoMax[servoNum] = serialCommunication.receivedCommandPartAsInt(2);
				}
			} else if (serialCommunication.receivedCommandPart(0)[0] == 'P') {
				// First sending the low limits
				serialCommunication.newCommandToSend();
				for (int i = 0; i < N; ++i) {
					serialCommunication.appendCommandPart(m_servoMin[i]);
				}
				serialCommunication.sendCommand();

				// Then sending the high limits
				serialCommunication.newCommandToSend();
				for (int i = 0; i < N; ++i) {
					serialCommunication.appendCommandPart(m_servoMax[i]);
				}
				serialCommunication.sendCommand();
			} else if (serialCommunication.receivedCommandPart(0)[0] == 'X') {
				// Exiting from the calibration procedure
				break;
			}
		}
	}
}

#endif
