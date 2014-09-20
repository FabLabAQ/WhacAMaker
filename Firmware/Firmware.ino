#include "serialCommunication.h"
#include "joystick.h"

// The baud rate to use for communication with computer
const long baudRate = 115200;

// Pin numbers: Joystick
const int joystickP1 = 52;
const int joystickP2 = 53;
const int joystickX = A14;
const int joystickY = A15;

const int tmpLed = 22;
const int tmpLedPWMX = 3;
const int tmpLedPWMY = 5;

// The object taking care of serial communication
SerialCommunication serialCommunication;

// The object taking care of reading joystick status
Joystick joystick;

void setup() {
	// Initializing serial communication
	serialCommunication.begin(baudRate);

	// Initialize joystick
	joystick.begin(joystickP1, joystickP2, joystickX, joystickY);

	// Initialize pins
	pinMode(tmpLed, OUTPUT);
	pinMode(tmpLedPWMX, OUTPUT);
	pinMode(tmpLedPWMY, OUTPUT);
}

void loop() {
// 	if (serialCommunication.commandReceived()) {
// 		// Sending back the command as is for debugging
// 		serialCommunication.newCommandToSend();
// 		serialCommunication.appendCommandPart("DEBUG");
// 		for (int i = 0; i < serialCommunication.receivedCommandNumParts(); i++) {
// 			serialCommunication.appendCommandPart(serialCommunication.receivedCommandPart(i));
// 		}
// 		serialCommunication.sendCommand();
//
// 		// Getting the command. We are interested in the second value, an int, which we return inceremented by 1
// 		if (serialCommunication.receivedCommandNumParts() >= 2) {
// 			int i = serialCommunication.receivedCommandPartAsInt(1);
//
// 			// Send reply
// 			serialCommunication.newCommandToSend();
// 			serialCommunication.appendCommandPart("PONG");
// 			serialCommunication.appendCommandPart(i + 1);
// 			serialCommunication.sendCommand();
// 		} else {
// 			// Send error
// 			serialCommunication.newCommandToSend();
// 			serialCommunication.appendCommandPart("ERROR");
// 			serialCommunication.sendCommand();
// 		}
// 	}
//
	delay(100);

	// Reading joystick and activating leds
	joystick.readStatus();

	// Activating leds with PWM
	analogWrite(tmpLedPWMX, joystick.xPosition() >> 4);
	analogWrite(tmpLedPWMY, joystick.yPosition() >> 4);

	if (joystick.button1Pressed() || joystick.button2Pressed()) {
		digitalWrite(tmpLed, HIGH);
	} else {
		digitalWrite(tmpLed, LOW);
	}

	serialCommunication.newCommandToSend();
	serialCommunication.appendCommandPart("J");
	serialCommunication.appendCommandPart(joystick.xPosition());
	serialCommunication.appendCommandPart(joystick.yPosition());
	serialCommunication.appendCommandPart(joystick.button1Pressed());
	serialCommunication.appendCommandPart(joystick.button2Pressed());
	serialCommunication.sendCommand();
}
