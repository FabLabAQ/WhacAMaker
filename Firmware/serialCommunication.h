#ifndef __SERIAL_COMMUNICATION_H__
#define __SERIAL_COMMUNICATION_H__

#include <stdlib.h>

/**
 * \brief A simple class which takes care of serial communication
 *
 * Commands can have at most maxCommandParts, other arguments are discarded.
 * Parts are separated by whitespaces, the command ends with a newline. Remember
 * to call begin() in the setup() function (see function description for an
 * explanation of why we can't call setup in the constructor)
 */
class SerialCommunication
{
public:
	/**
	 * \brief The maximum number of parts in a command
	 */
	static const int maxCommandParts = 10;

	/**
	 * \brief The maximum length of a command
	 */
	static const int maxCommandLength = 32;

public:
	/**
	 * \brief Constructor
	 */
	SerialCommunication();

	/**
	 * \brief Initializes serial communication
	 *
	 * We can't call Serial.begin() in the constructor because it is called
	 * too early in the initialization. So we must call this function inside
	 * setup()
	 * \param baudRate the baud rate
	 */
	void begin(long baudRate);

	/**
	 * \brief Returns true if a command has been received
	 *
	 * This checks if a command is available and parses it. After calling
	 * this function the previously received command is removed (even if we
	 * haven't received a new command yet). Even when this returns false,
	 * data can still be read via the serial line (e.g. if a command hasn't
	 * fully arrived yet)
	 * \return true if a command has been received
	 */
	bool commandReceived();

	/**
	 * \brief The number of parts in the received command
	 *
	 * This is only valid after commandReceived returns true
	 * \return the number of parts in the command
	 */
	int receivedCommandNumParts() const
	{
		return m_numParts;
	}

	/**
	 * \brief The i-th part of the received command as a string
	 *
	 * This is only valid after commandReceived returns true
	 * \param i the part to return
	 * \return the i-th part of the received command as a string
	 */
	const char* receivedCommandPart(int i) const
	{
		return &(m_receivedCommand[m_startingPartIndex[i]]);
	}

	/**
	 * \brief The i-th part of the received command as an int
	 *
	 * This is only valid after commandReceived returns true
	 * \param i the part to return
	 * \return the i-th part of the received command as an int
	 */
	int receivedCommandPartAsInt(int i) const
	{
		return atoi(receivedCommandPart(i));
	}

	/**
	 * \brief The i-th part of the received command as a float
	 *
	 * This is only valid after commandReceived returns true
	 * \param i the part to return
	 * \return the i-th part of the received command as a float
	 */
	float receivedCommandPartAsFloat(int i) const
	{
		return atof(receivedCommandPart(i));
	}

	/**
	 * \brief Creates a new command to send
	 *
	 * After calling this function you can start appending command parts
	 * with the appendCommandPart() function, which adds parts separated by
	 * a whitespace
	 */
	void newCommandToSend();

	/**
	 * \brief Adds a part to the command to send
	 *
	 * Use this for strings
	 * \param part the part to add
	 */
	void appendCommandPart(const char* part);

	/**
	 * \brief Adds a part to the command to send
	 *
	 * Use this for integers
	 * \param part the part to add
	 */
	void appendCommandPart(int part);

	/**
	 * \brief Adds a part to the command to send
	 *
	 * Use this for floats
	 * \param part the part to add
	 */
	void appendCommandPart(float part);

	/**
	 * \brief Sends the last command
	 *
	 * If called multiple times without calling newCommandToSend() first,
	 * sends the same command over and over again
	 */
	void sendCommand();

private:
	/**
	 * \brief The received command
	 *
	 * In this buffer, parts are separated by '\0' (they replace
	 * whitespaces). The +1 is to contain the final '\0'
	 */
	char m_receivedCommand[maxCommandLength + 1];

	/**
	 * \brief The actual length of the received command
	 */
	int m_receivedCommandLength;

	/**
	 * \brief The index at which received command parts start.
	 */
	int m_startingPartIndex[maxCommandParts];

	/**
	 * \brief The number of parts of the received command
	 */
	int m_numParts;

	/**
	 * \brief True if we have received a complete command
	 */
	bool m_commandReceived;

	/**
	 * \brief The command to send
	 *
	 * Here the command is where the command is built. the +2 is for the
	 * final "\n\0"
	 */
	char m_commandToSend[maxCommandLength + 2];

	/**
	 * \brief The actual length of the command to send
	 */
	int m_commandToSendLength;
};

#endif
