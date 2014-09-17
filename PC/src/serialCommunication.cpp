#include "serialCommunication.h"
#include "myRuntimeException.h"
#include "controller.h"
#include <iostream>

#warning DECIDERE SE METTERE IL CHECK ALLA FINE DEL COMANDO O NO

SerialCommunication::SerialCommunication(Controller* controller, QObject* parent) :
	QObject(parent),
	m_controller(controller),
	m_serialPort(),
	m_incomingData()
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

void SerialCommunication::sendCommand(QString command)
{
	QByteArray dataToSend = command.toLatin1();
	if (dataToSend.at(dataToSend.size() - 1) != '\n') {
		dataToSend.append('\n');
	}
	qint64 bytesWritten = m_serialPort.write(dataToSend);

	if (bytesWritten == -1) {
		std::cerr  << "Error writing data, error: " << m_serialPort.errorString().toLatin1().data() << std::endl;
	} else if (bytesWritten != dataToSend.size()) {
		std::cerr  << "Cannot write all data, error: " << m_serialPort.errorString().toLatin1().data() << std::endl;
	}
}

void SerialCommunication::handleReadyRead()
{
	// Adding data to the buffer
	m_incomingData.append(m_serialPort.readAll());

	int newlinePos = m_incomingData.indexOf('\n');
	if (newlinePos != -1) {
		// Taking the command. HEre we also remove the newline from it
		QString command = m_incomingData.left(newlinePos);

		// Removing the command we just received from the buffer
		m_incomingData = m_incomingData.mid(newlinePos + 1);

		// Sending command to controller
		m_controller->commandReceived(command);
	}
}

void SerialCommunication::handleError(QSerialPort::SerialPortError error)
{
	std::cerr << "Serial Communication error, code: " << error << std::endl;
}

