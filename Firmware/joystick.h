#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

/**
 * \brief The class to read input from joystick
 */
class Joystick
{
public:
	/**
	 * \brief Constructor
	 */
	Joystick();

	/**
	 * \brief Initializes stuffs for the joystick
	 *
	 * We can't do this in the constructor because it is called too early in
	 * the initialization. So we must call this function inside setup()
	 * \param p1 the digital input pin of button 1
	 * \param p2 the digital input pin of button 2
	 * \param x the analog input pin for the x axis
	 * \param y the analog input pin for the y axis
	 */
	void begin(int p1, int p2, int x, int y);

	/**
	 * \brief Reads the position of axes and the status of buttons
	 *
	 * After calling this function you can access the positions of axes and
	 * the status of buttons
	 */
	void readStatus();

	/**
	 * \brief Returns whether button 1 is pressed or not
	 *
	 * This is the status the last time readStatus was called
	 * \return true if button 1 is pressed, false otherwise
	 */
	bool button1Pressed() const
	{
		return m_button1Pressed;
	}

	/**
	 * \brief Returns whether button 2 is pressed or not
	 *
	 * This is the status the last time readStatus was called
	 * \return true if button 2 is pressed, false otherwise
	 */
	bool button2Pressed() const
	{
		return m_button2Pressed;
	}

	/**
	 * \brief Returns the position of the x axis
	 *
	 * This is an integer value betwee 0 and 1024.  This is the status the
	 * last time readStatus was called
	 * \return the position of the x axis
	 */
	int xPosition() const
	{
		return m_xPosition;
	}

	/**
	 * \brief Returns the position of the y axis
	 *
	 * This is an integer value betwee 0 and 1024.  This is the status the
	 * last time readStatus was called
	 * \return the position of the y axis
	 */
	int yPosition() const
	{
		return m_yPosition;
	}

private:
	/**
	 * \brief The digital input pin of button 1
	 */
	int m_pinP1;

	/**
	 * \brief The digital input pin of button 2
	 */
	int m_pinP2;

	/**
	 * \brief The analog input pin for the x axis
	 */
	int m_pinX;

	/**
	 * \brief The analog input pin for the y axis
	 */
	int m_pinY;

	/**
	 * \brief True if button 1 is pressed, false otherwise
	 */
	bool m_button1Pressed;

	/**
	 * \brief True if button 2 is pressed, false otherwise
	 */
	bool m_button2Pressed;

	/**
	 * \brief The position of the x axis
	 *
	 * This is an integer value betwee 0 and 1024, i.e. the reading of the
	 * analog pin
	 */
	int m_xPosition;

	/**
	 * \brief The position of the y axis
	 *
	 * This is an integer value betwee 0 and 1024, i.e. the reading of the
	 * analog pin
	 */
	int m_yPosition;
};

#endif
