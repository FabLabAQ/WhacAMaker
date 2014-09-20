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

void setup() {
	// Initializing serial communication
	serialCommunication.begin(baudRate);

	// Initializing joystick
	joystick.begin(joystickP1, joystickP2, joystickX, joystickY);
}

void loop() {
	// Reading joystick and sending activations
	joystick.readStatus();

	serialCommunication.newCommandToSend();
	serialCommunication.appendCommandPart("J");
	serialCommunication.appendCommandPart(joystick.xPosition());
	serialCommunication.appendCommandPart(joystick.yPosition());
	serialCommunication.appendCommandPart(joystick.button1Pressed());
	serialCommunication.appendCommandPart(joystick.button2Pressed());
	serialCommunication.sendCommand();
}
