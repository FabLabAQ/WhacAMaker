#include "serialCommunication.h"
#include "joystick.h"

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

// Whether to send joystick positions or not
bool sendJoystick = false;

void setup() {
	// Initializing serial communication
	serialCommunication.begin(baudRate);

	// Initializing joystick
	joystick.begin(joystickP1, joystickP2, joystickX, joystickY);
}

void loop() {
	// Reading from the serial line
	if (serialCommunication.commandReceived() && (serialCommunication.receivedCommandNumParts() != 0)) {
		if (serialCommunication.receivedCommandPart(0)[0] == 'S') {
			sendJoystick = true;
		} else if (serialCommunication.receivedCommandPart(0)[0] == 'M') {
			// Move servo to bring up or down the moles
			// Check arduino int dimension: if it is at least 2 byte, we can send the list of moles to bring up or down as bits (if the i-th bit is 1 the i-th mole goes/stays up, if it s 0, it goes/stays down)
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
