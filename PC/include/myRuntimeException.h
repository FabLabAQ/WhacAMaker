#ifndef __MY_RUNTIME_EXCEPTION_H__
#define __MY_RUNTIME_EXCEPTION_H__

#include <QException>
#include <QString>
#include <cstring>
#include <cstdio>

/**
 * \brief The exception thrown whenever a runtime error occurs
 *
 * The message length is always cut at 1023 characters
 */
class MyRuntimeException : public QException
{
public:
	/**
	 * \brief Constructor
	 *
	 * \param message the error message. The buffer for this is at most 1024
	 *                characters (including the '\0' terminator)
	 */
	MyRuntimeException(const char* message) throw() :
		QException()
	{
		strncpy(m_errorMessage, message, 1024);
		m_errorMessage[1023] = '\0';
	}

	/**
	 * \brief Copy constructor
	 *
	 * \param other the exception to copy
	 */
	MyRuntimeException(const MyRuntimeException& other) throw() :
		QException(other)
	{
		strncpy(m_errorMessage, other.m_errorMessage, 1024);
		m_errorMessage[1023] = '\0';
	}

	/**
	 * \brief Copy operator
	 *
	 * \param other the exception to copy
	 */
	MyRuntimeException& operator=(const MyRuntimeException& other) throw()
	{
		if (&other == this) {
			return *this;
		}

		QException::operator=(other);
		strncpy(m_errorMessage, other.m_errorMessage, 1024);
		m_errorMessage[1023] = '\0';

		return *this;
	}

	/**
	 * \brief Destructor
	 */
	virtual ~MyRuntimeException() throw()
	{
	}

	/**
	 * \brief Returns a C string describing the exception
	 *
	 * \return a C string describing the exception
	 */
	virtual const char *what() const throw()
	{
		return m_errorMessage;
	}

	/**
	 * \brief Returns a clone of this class
	 *
	 * \return a clone of this object
	 */
	virtual MyRuntimeException* clone() const
	{
		return new MyRuntimeException(*this);
	}

	/**
	 * \brief Raised this as an exception
	 */
	virtual void raise() const
	{
		throw *this;
	}

private:
	/**
	 * \brief The message describing the error
	 */
	char m_errorMessage[1024];
};

/**
 * \brief An helper function to throw MyRuntimeException
 *
 * This takes a QString as argument instead of a C string
 * \param message the error message
 */
inline void throwMyRuntimeException(QString reason)
{
	throw MyRuntimeException(reason.toLatin1().data());
}

#endif
