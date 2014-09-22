#include "serialCommunication.h"
#include "myRuntimeException.h"
#include "controller.h"
#include <iostream>

#include <unistd.h>
#warning DECIDERE SE METTERE IL CHECK ALLA FINE DEL COMANDO O NO

SerialCommunication::SerialCommunication(Controller* controller, QObject* parent)
	: QObject(parent)
	, m_controller(controller)
	, m_serialPort()
	, m_incomingData()
	, m_endCommandPosition(-1)
	, m_receivedCommandParts()
	, m_commandPartsToSend()
{
	// Connecting signals from the serial port
	connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
	connect(&m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
}

SerialCommunication::~SerialCommunication()
{
}

void SerialCommunication::setSerialPort(QString port)
{
	// Closing the old port
	if (m_serialPort.isOpen()) {
		m_serialPort.close();
		m_serialPort.clearError();
	}

	// Setting the name of the port
	m_serialPort.setBaudRate(115200);
	m_serialPort.setPortName(port);

	// Trying to open the port
	if (!m_serialPort.open(QIODevice::ReadWrite)) {
		// Here we can't throw an exception because otherwise it would be impossible to change the settings
		// Simply printing a message to stderr
		std::cerr << "Error opening serial port at " << port.toLatin1().data() << std::endl;
	}

	std::cerr << "Serial port opened, error: " << m_serialPort.error() << ", open: " << m_serialPort.isOpen() << std::endl;
	m_serialPort.write("S\n");
//	write(m_serialPort.handle(), "S\n", 2);
	std::cerr << "Tried to write, error: " << m_serialPort.error() << ", open: " << m_serialPort.isOpen() << std::endl;
}

bool SerialCommunication::extractReceivedCommand()
{
	if (m_endCommandPosition == -1) {
		return false;
	}

	// Taking the command. Here we don't take the closing newline. Wehn we split we keep empty parts to have
	// a behavior compliant with the one on Arduino
	QString command = m_incomingData.left(m_endCommandPosition);
	m_receivedCommandParts = command.split(' ', QString::KeepEmptyParts);

	// Removing data for the extracted command from the queue
	m_incomingData = m_incomingData.mid(m_endCommandPosition + 1);

	// Now fixing m_endCommandPosition
	m_endCommandPosition = m_incomingData.indexOf('\n');

std::cerr << "===extractReceivedCommand=== command: \"" << command.toLatin1().data() << "\", m_endCommandPosition: " << m_endCommandPosition << ", all data: \"" << m_incomingData.data() << "\"" << std::endl;

	return true;
}

int SerialCommunication::receivedCommandNumParts() const
{
	return m_receivedCommandParts.size();
}

QString SerialCommunication::receivedCommandPart(int i) const
{
	return m_receivedCommandParts[i];
}

int SerialCommunication::receivedCommandPartAsInt(int i) const
{
	return m_receivedCommandParts[i].toInt();
}

float SerialCommunication::receivedCommandPartAsFloat(int i) const
{
	return m_receivedCommandParts[i].toFloat();
}

void SerialCommunication::newCommandToSend()
{
	m_commandPartsToSend.clear();
}

void SerialCommunication::appendCommandPart(QString part)
{
	if (m_commandPartsToSend.size() != 0) {
		m_commandPartsToSend.append(' ');
	}

	m_commandPartsToSend.append(part.toLatin1());
}

void SerialCommunication::appendCommandPart(int part)
{
	appendCommandPart(QString::number(part));
}

void SerialCommunication::appendCommandPart(float part)
{
	appendCommandPart(QString::number(part));
}

void SerialCommunication::sendCommand()
{
	// Adding the final endline
	m_commandPartsToSend.append('\n');

	// Writing data
	qint64 bytesWritten = m_serialPort.write(m_commandPartsToSend);

std::cerr << "Command sent: " << m_commandPartsToSend.data() << std::endl;

	if (bytesWritten == -1) {
		std::cerr  << "Error writing data, error: " << m_serialPort.errorString().toLatin1().data() << std::endl;
	} else if (bytesWritten != m_commandPartsToSend.size()) {
		std::cerr  << "Cannot write all data, error: " << m_serialPort.errorString().toLatin1().data() << std::endl;
	}
}

void SerialCommunication::handleReadyRead()
{
	// Getting data
	QByteArray newData = m_serialPort.readAll();

	// Adding data to the buffer. We have to save the previous size of m_incomingData to
	// have the correct m_endCommandPosition
	const int oldSize = m_incomingData.size();
	m_incomingData.append(newData);

	// Now looking in new data for the first '\n' and the number of them
	int firstNewlinePos = -1;
	int numNewlines = 0;
	for (int i = 0; i < newData.size(); i++) {
		if (newData[i] == '\n') {
			if (firstNewlinePos == -1) {
				firstNewlinePos = i + oldSize;
			}
			++numNewlines;
		}
	}

std::cerr << "===handleReadyRead=== new data: \"" << newData.data() << "\", oldSize: " << oldSize << ", firstNewlinePos: " << firstNewlinePos << ", numNewlines: " << numNewlines << ", m_endCommandPosition: " << m_endCommandPosition << ", all data: \"" << m_incomingData.data() << "\"" << std::endl;

	// If there was at least one '\n' in the new data, checking what to do
	if (numNewlines != 0) {
		// If there was no command in the queue, saving the position of the '\n' of the first
		// command (which is the first one)
		if (m_endCommandPosition == -1) {
			m_endCommandPosition = firstNewlinePos;
		}

		// Now telling the controller we have received commands. We call commandReceived() once for each
		// received command
		for (int i = 0; i < numNewlines; i++) {
			m_controller->commandReceived();
		}
	}
}

void SerialCommunication::handleError(QSerialPort::SerialPortError error)
{
	std::cerr << "Serial Communication error, code: " << error << std::endl;
}

