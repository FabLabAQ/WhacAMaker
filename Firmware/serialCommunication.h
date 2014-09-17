#ifndef __SERIAL_COMMUNICATION_H__
#define __SERIAL_COMMUNICATION_H__

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
	 * haven't received a new command yet)
	 * \return true if a command has been received
	 */
	bool commandReceived();

	/**
	 * \brief The number of parts in the command
	 *
	 * This is only valid after commandReceived returns true
	 * \return the number of parts in the command
	 */
	int receivedCommandNumParts() const;

	/**
	 * \brief The i-th part of the command as a string
	 *
	 * This is only valid after commandReceived returns true
	 * \param i the part to return
	 * \return the i-th part of the command as a string
	 */
	const char* receivedCommandPart(int i) const;

private:
	/**
	 * \brief The received command
	 *
	 * In this buffer, parts are separated by '\0' (they replace
	 * whitespaces)
	 */
	char m_receivedCommand[maxCommandLength + 1];

	/**
	 * \brief The actual length of the command
	 */
	int m_commandLength;

	/**
	 * \brief The index at which command parts start.
	 */
	int m_startingPartIndex[maxCommandParts];

	/**
	 * \brief The number of parts of the command
	 */
	int m_numParts;

	/**
	 * \brief True if we have received a complete command
	 */
	bool m_commandReceived;
};

#endif
