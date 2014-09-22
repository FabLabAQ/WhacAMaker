#include "serialCommunication.h"
#include "Arduino.h"

SerialCommunication::SerialCommunication() :
	m_receivedCommandLength(0),
	m_numParts(1),
	m_commandReceived(false),
	m_commandToSendLength(0)
{
	// The last element of m_receivedCommand is always '\0'
	m_receivedCommand[maxCommandLength] = '\0';

	// We also initialize the starting index of the first part to 0
	m_startingPartIndex[0] = 0;

	// Setting the last two elements od the m_commandToSend vector to "\n\0" to avoid problems. Also
	// setting the first element to '\0'
	m_commandToSend[0] = '\0';
	m_commandToSend[maxCommandLength] = '\n';
	m_commandToSend[maxCommandLength + 1] = '\0';
}

void SerialCommunication::begin(long baudRate)
{
	Serial.begin(baudRate);
}

bool SerialCommunication::commandReceived()
{
	// If we are storing a command, we have to reset our internal storage before reading again
	if (m_commandReceived) {
		m_receivedCommandLength = 0;
		// There is always at least one part
		m_numParts = 1;
		m_commandReceived = false;
	}

	// Copying into our buffer until there is data or we reach a newline
	while (Serial.available() > 0) {
		const int datum = Serial.read();

		if ((datum == '\n') || (m_receivedCommandLength >= maxCommandLength)){
			// Adding the final '\0'. We get here also if command is too long, in that case
			// we simply cut the command
			m_receivedCommand[m_receivedCommandLength] = '\0';
			m_commandReceived = true;

			break;
		} else if (m_receivedCommandLength < maxCommandLength) {
			if (datum == ' ') {
				if (m_numParts < maxCommandParts) {
					m_startingPartIndex[m_numParts++] = m_receivedCommandLength + 1;
				}
				m_receivedCommand[m_receivedCommandLength] = '\0';
			} else {
				m_receivedCommand[m_receivedCommandLength] = datum;
			}

			m_receivedCommandLength++;
		}
	}

	return m_commandReceived;
}

void SerialCommunication::newCommandToSend()
{
	m_commandToSend[0] = '\0';

	m_commandToSendLength = 0;
}

void SerialCommunication::appendCommandPart(const char* part)
{
	if (m_commandToSendLength != 0) {
		m_commandToSend[m_commandToSendLength++] = ' ';
	}

	for (int i = 0; (m_commandToSendLength < maxCommandLength) && (part[i] != '\0'); ++i, ++m_commandToSendLength) {
		m_commandToSend[m_commandToSendLength] = part[i];
	}

	m_commandToSendLength[m_commandToSend] = '\n';
	m_commandToSendLength[m_commandToSend + 1] = '\0';
}

void SerialCommunication::appendCommandPart(int part)
{
	// Using String to convert the int and then calling appendCommandPart for strings. tmp is for conversion,
	// 64 characters should be enough
	char tmp[64];
	String(part).toCharArray(tmp, 64);
	appendCommandPart(tmp);
}

void SerialCommunication::appendCommandPart(float part)
{
	// Using dtostrf to convert the float to string and calling appendCommandPart for string. tmp is for
	// dtostrf, 64 characters should be enough
	char tmp[64];
	appendCommandPart(dtostrf(part, 1, 3, tmp));
}

void SerialCommunication::sendCommand()
{
	Serial.write(m_commandToSend);
}
