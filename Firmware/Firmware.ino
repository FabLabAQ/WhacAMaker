#include "serialCommunication.h"
#include "joystick.h"
#include "moles.h"

// We need this here otherwise moles.h doesn't compile (the compiler can't find
// Servo.h)
#include <Servo.h>

// The baud rate to use for communication with computer
const long baudRate = 115200;

// Pin numbers: Joystick
const int joystickP1 = 52;
const int joystickP2 = 53;
const int joystickX = A14;
const int joystickY = A15;

// The object taking care of serial communication
SerialCommunication serialCommunication;

// The object taking care of reading joystick status
Joystick joystick;

// The object managing the moles and the moles pins (we can use any digital
// output, the Servo library uses a timer interrupt to generate the PWM, not the
// hardware PWM)
int molesPins[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
typedef Moles<9> GameMoles;
GameMoles moles;

// Whether to send joystick positions or not
bool sendJoystick = false;

void setup() {
	// Initializing serial communication
	serialCommunication.begin(baudRate);

	// Initializing joystick
	joystick.begin(joystickP1, joystickP2, joystickX, joystickY);

	// Initializing moles
	moles.begin(molesPins);
}

void loop() {
	// Reading from the serial line
	if (serialCommunication.commandReceived() && (serialCommunication.receivedCommandNumParts() != 0)) {
		if (serialCommunication.receivedCommandPart(0)[0] == 'S') {
			sendJoystick = true;
		} else if ((serialCommunication.receivedCommandPart(0)[0] == 'M') && (serialCommunication.receivedCommandNumParts() >= 2)) {
			// Move servo to bring up or down the moles
			moles.setStatus(serialCommunication.receivedCommandPartAsInt(1));
		}
	}

	if (sendJoystick) {
		// Reading joystick and sending activations
		joystick.readStatus();

		serialCommunication.newCommandToSend();
		serialCommunication.appendCommandPart("J");
		serialCommunication.appendCommandPart(joystick.xPosition());
		serialCommunication.appendCommandPart(joystick.yPosition());
		serialCommunication.appendCommandPart(joystick.button1Pressed());
		serialCommunication.appendCommandPart(joystick.button2Pressed());
		serialCommunication.sendCommand();

// 		// This is just to avoid flooding the PC
// 		delay(50);
	}
}
