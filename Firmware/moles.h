#ifndef __MOLES_H__
#define __MOLES_H__

#include <Arduino.h>
#include <Servo.h>

/**
 * \brief The class to manage moles
 *
 * The template parameter N is the number of moles. The pins for the pwm are
 * passed to the begin function, along with the limits. There can be at most 10
 * moles
 */
template <unsigned int N>
class Moles
{
public:
	/**
	 * \brief The possible status of a mole (either UP or DOWN)
	 */
	enum Status {DOWN = 0, UP = 1};

public:
	/**
	 * \brief Constructor
	 */
	Moles();

	/**
	 * \brief Initializes stuffs for the moles
	 *
	 * We can't do this in the constructor because it is called too early in
	 * the initialization. So we must call this function inside setup().
	 * This doesn't attach servos, only saves pins and limits
	 * \param molesPins the array with pins to use for moles. The array must
	 *                  have at least N elements
	 * \param servoMin the minimum pulse for servos (corresponding to 0
	 *                 degrees)
	 * \param servoMax the maximum pulse for servos (corresponding to 180
	 *                 degrees)
	 */
	void begin(int molesPins[], int servoMin[], int servoMax[]);

	/**
	 * \brief Attaches servos
	 */
	void attach();

	/**
	 * \brief Detaches servos
	 */
	void detach();

	/**
	 * \brief Sets the status of moles
	 *
	 * This function changes the status of all moles at once.
	 * \param status the new status. Each bit corresponds to a mole, 1 means
	 *               that the mole is up, 0 that it is down. The least
	 *               significant bit refers to the first mole.
	 */
	void setStatus(unsigned int status);

	/**
	 * \brief Returns the status of all moles
	 *
	 * See setStatus for how to interpret the returned status
	 * \return the status of all moles
	 */
	unsigned int getStatus() const;

	/**
	 * \brief Sets the status of the i-th mole
	 *
	 * \param i the id of the mole
	 * \param status the new status
	 */
	void setMoleStatus(unsigned int i, Status status);

	/**
	 * \brief Returns the status of the i-th mole
	 *
	 * \param i the id of the mole
	 * \return the status of the mole
	 */
	Status getMoleStatus(unsigned int i) const;

	/**
	 * \brief Sets the mole to the given postion, using
	 *        Servo::writeMicroseconds
	 *
	 * Use this function only during a calibration procedure
	 * \param i the servo to move (must be between 0 and N-1)
	 * \param v the value to use when calling Servo::writeMicroseconds()
	 */
	void setServoPositionRaw(int i, int v);

private:
	/**
	 * \brief Sets moves the i-th mole
	 *
	 * \param i the index of the mole to move
	 * \param status the new status of the mole
	 */
	void moveMole(unsigned int i, Status status);

	/**
	 * \brief The status of moles
	 */
	unsigned int m_status;

	/**
	 * \brief The servos controlling the moles
	 */
	Servo m_servos[N];

	/**
	 * \brief The pins of the servos controlling the moles
	 */
	int m_molesPins[N];

	/**
	 * \brief The minimum value for servos
	 */
	int m_servoMin[N];

	/**
	 * \brief The maxumum value for servos
	 */
	int m_servoMax[N];

	/**
	 * \brief A typedef for compile-time check that N is no more than 10
	 */
	typedef char NoMoreThan10MolesAllowed[(N > 10) ? -1 : 1];
};

// Template implementation of all methods

template <unsigned int N>
Moles<N>::Moles()
	: m_status(0) // All moles down
{
	// Initializing pins and limits to null values
	for (int i = 0; i < N; i++) {
		m_molesPins[i] = 0;
		m_servoMin[i] = 1000;
		m_servoMax[i] = 1000;
	}
}

template <unsigned int N>
void Moles<N>::begin(int molesPins[], int servoMin[], int servoMax[])
{
	// Saving pins and limits
	for (int i = 0; i < N; i++) {
		m_molesPins[i] = molesPins[i];
		m_servoMin[i] = servoMin[i];
		m_servoMax[i] = servoMax[i];
	}
}

template <unsigned int N>
void Moles<N>::attach()
{
	// Attaching mole pins to servos and moving them all down
	for (int i = 0; i < N; i++) {
		m_servos[i].attach(m_molesPins[i], m_servoMin[i], m_servoMax[i]);
	}
	setStatus(0);
}

template <unsigned int N>
void Moles<N>::detach()
{
	// Attaching mole pins to servos and moving them all down
	for (int i = 0; i < N; i++) {
		m_servos[i].detach();
	}
}

template <unsigned int N>
void Moles<N>::setStatus(unsigned int status)
{
	// Storing status, removing the higher order, unused bits
	m_status = status & ((1 << (N + 1)) - 1);

	// Now setting the status for all moles
	for (int i = 0; i < N; i++) {
		moveMole(i, static_cast<Status>((m_status >> i) & 1));
	}
}

template <unsigned int N>
unsigned int Moles<N>::getStatus() const
{
	return m_status;
}

template <unsigned int N>
void Moles<N>::setMoleStatus(unsigned int i, Status status)
{
	m_status |= (status & 1) << i;
	moveMole(i, status);
}

template <unsigned int N>
typename Moles<N>::Status Moles<N>::getMoleStatus(unsigned int i) const
{
	return static_cast<Status>((m_status >> i) & 1);
}

template <unsigned int N>
void Moles<N>::setServoPositionRaw(int i, int v)
{
	if ((i < 0) || (i >= N)) {
		return;
	}

	m_servos[i].writeMicroseconds(v);
}

template <unsigned int N>
void Moles<N>::moveMole(unsigned int i, Status status)
{
	if (status == DOWN) {
		m_servos[i].write(0);
	} else {
		m_servos[i].write(180);
	}
}

#endif
