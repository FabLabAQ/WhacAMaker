#ifndef __SERIAL_COMMUNICATION_H__
#define __SERIAL_COMMUNICATION_H__

#include <QSerialPort>
#include <QObject>

/**
 * \brief The class handling the communication with Arduino through the serial
 *        port
 */
class SerialCommunication : public QObject
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor
	 *
	 * \param parent the parent object
	 */
	SerialCommunication(QObject* parent = NULL);

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

private slots:
	/**
	 * \brief The slot called when data has been written
	 *
	 * \param bytes the bytes that have actually been written
	 */
	void handleBytesWritten(qint64 bytes);

	/**
	 * \brief The slot called when there is data ready to be read
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
	 * \brief The serial communication port
	 */
	QSerialPort m_serialPort;
};

#endif
