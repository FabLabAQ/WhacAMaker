#include "serialCommunication.h"
#include "myRuntimeException.h"
#include <iostream>

SerialCommunication::SerialCommunication(QObject* parent) :
	QObject(parent),
	m_serialPort()
{
	// Connecting signals from the serial port
	connect(&m_serialPort, SIGNAL(bytesWritten(qint64)), this, SLOT(handleBytesWritten(qint64)));
	connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
	connect(&m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
}

SerialCommunication::~SerialCommunication()
{
}

void SerialCommunication::setSerialPort(QString port)
{
	// Closing the old port
	m_serialPort.close();

	// Setting the name of the port
	m_serialPort.setBaudRate(115200);
	m_serialPort.setPortName(port);

	// Trying to open the port
	if (!m_serialPort.open(QIODevice::ReadWrite)) {
		m_serialPort.clearError();

		// Here we can't throw an exception because otherwise it would be impossible to change the settings
		// Simply printing a message to stderr
		std::cerr << "Error opening serial port at " << port.toLatin1().data() << std::endl;
	}
}

void SerialCommunication::handleBytesWritten(qint64 bytes)
{
// 	sadfdsafdsaf
}

void SerialCommunication::handleReadyRead()
{
	QByteArray data = m_serialPort.readAll();

	std::cerr << "Data arrived: " << data.data() << std::endl;
}

void SerialCommunication::handleError(QSerialPort::SerialPortError error)
{
// 	dsfgdfsgdfsg
}
