#ifndef __SERIAL_COMMUNICATION_H__
#define __SERIAL_COMMUNICATION_H__

#include <QSerialPort>
#include <QByteArray>
#include <QObject>
#include <QStringList>

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
	 * \brief Returns true if a command has been received and extracts the
	 *        command from the queue
	 *
	 * Ater a call to this function returns true, you can get command parts
	 * with receivedCommandParts*() functions
	 * \return true if a command has been received
	 */
	bool extractReceivedCommand();

	/**
	 * \brief The number of parts in the received command
	 *
	 * This is only valid after extractReceivedCommand returns true
	 * \return the number of parts in the the received command
	 */
	int receivedCommandNumParts() const;

	/**
	 * \brief The i-th part of the received command as a string
	 *
	 * This is only valid after extractReceivedCommand returns true
	 * \param i the part to return
	 * \return the i-th part of the received command as a string
	 */
	QString receivedCommandPart(int i) const;

	/**
	 * \brief The i-th part of the received command as an int
	 *
	 * This is only valid after extractReceivedCommand returns true
	 * \param i the part to return
	 * \return the i-th part of the received command as an int
	 */
	int receivedCommandPartAsInt(int i) const;

	/**
	 * \brief The i-th part of the received command as a float
	 *
	 * This is only valid after extractReceivedCommand returns true
	 * \param i the part to return
	 * \return the i-th part of the received command as a float
	 */
	float receivedCommandPartAsFloat(int i) const;

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
	void appendCommandPart(QString part);

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

	/**
	 * \brief When different from -1, a command has been received and is in
	 *        m_incomingData from position 0 to this position
	 */
	int m_endCommandPosition;

	/**
	 * \brief The list of received command parts
	 */
	QStringList m_receivedCommandParts;

	/**
	 * \brief The buffer with parts of the command to send
	 */
	QByteArray m_commandPartsToSend;
};

#endif
