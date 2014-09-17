#ifndef __SERIAL_COMMUNICATION_H__
#define __SERIAL_COMMUNICATION_H__

#include <QSerialPort>
#include <QByteArray>
#include <QObject>
#include <QTimer>

class Controller;

/**
 * \brief The class handling the communication with Arduino through the serial
 *        port
 *
 * This class doesn't throw in case of errors, it simply prints messages to
 * stderr
 */
class SerialCommunication : public QObject
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor
	 *
	 * \param controller the controller object of the game
	 * \param parent the parent object
	 */
	SerialCommunication(Controller* controller, QObject* parent = NULL);

	/**
	 * \brief Destructor
	 */
	~SerialCommunication();

	/**
	 * \brief Sets the serial port to use and opens it
	 *
	 * \param port the name of the port to use
	 */
	void setSerialPort(QString port);

	/**
	 * \brief Sends a command through the serial port
	 *
	 * This function automatically adds a newline to terminate the command
	 * if not present
	 * \param command the commad to send
	 */
	void sendCommand(QString command);

private slots:
	/**
	 * \brief The slot called when there is data ready to be read
	 *
	 * This calls the commandReceived function of controller
	 */
	void handleReadyRead();

	/**
	 * \brief The function called when there is an error in the serial
	 *        communication
	 *
	 * \param error the error code
	 */
	void handleError(QSerialPort::SerialPortError error);

private:
	/**
	 * \brief The controller object of the game
	 */
	Controller* const m_controller;

	/**
	 * \brief The serial communication port
	 */
	QSerialPort m_serialPort;

	/**
	 * \brief The buffer of data from the serial port
	 */
	QByteArray m_incomingData;
};

#endif
