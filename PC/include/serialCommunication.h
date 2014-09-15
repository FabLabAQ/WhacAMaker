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

private:
	/**
	 * \brief The serial communication port
	 */
	QSerialPort m_serialPort;
};

#endif
