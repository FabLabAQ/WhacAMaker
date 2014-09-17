#include "serialCommunication.h"
#include "Arduino.h"

SerialCommunication::SerialCommunication() :
	m_commandLength(0),
	m_numParts(1),
	m_commandReceived(false)
{
	// The last element of m_receivedCommand is always '\0'
	m_receivedCommand[maxCommandLength] = '\0';

	// We also initialize the starting index of the first part to 0
	m_startingPartIndex[0] = 0;
}

void SerialCommunication::begin(long baudRate)
{
	Serial.begin(baudRate);
}

bool SerialCommunication::commandReceived()
{
	// If we are storing a command, we have to reset our internal storage before reading again
	if (m_commandReceived) {
		m_commandLength = 0;
		// There is always at least one part
		m_numParts = 1;
		m_commandReceived = false;
	}

	// Copying into our buffer until there is data or we reach a newline
	while (Serial.available() > 0) {
		const int datum = Serial.read();

		if (datum == '\n') {
			// Adding the final '\0'
			m_receivedCommand[m_commandLength] = '\0';
			m_commandReceived = true;

			break;
		} else if (m_commandLength < maxCommandLength) {
			if (datum == ' ') {
				if (m_numParts < maxCommandParts) {
					m_startingPartIndex[m_numParts++] = m_commandLength + 1;
				}
				m_receivedCommand[m_commandLength] = '\0';
			} else {
				m_receivedCommand[m_commandLength] = datum;
			}

			m_commandLength++;
		}
	}

	return m_commandReceived;
}

int SerialCommunication::receivedCommandNumParts() const
{
	return m_numParts;
}

const char* SerialCommunication::receivedCommandPart(int i) const
{
	return &(m_receivedCommand[m_startingPartIndex[i]]);
}
