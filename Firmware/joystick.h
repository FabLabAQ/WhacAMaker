#ifndef __JOYSTICK__
#define __JOYSTICK__

/**
 * \brief The class to read input from joystick
 */
class Joystick
{
	/**
	 * \brief Constructor
	 */
	Joystick();

	/**
	 * \brief Initializes stuffs for the joystick
	 *
	 * We can't do this in the constructor because it is called too early in
	 * the initialization. So we must call this function inside setup()
	 * \param ???
	 */
	void begin(PASSARE I PIN DI ASSI E PULSANTI);
};

#endif
