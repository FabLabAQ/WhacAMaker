#include "serialCommunication.h"

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

void setup() {
	// Initializing serial communication
	serialCommunication.begin(baudRate);

	// Initialize pins
	pinMode(joystickP1, INPUT_PULLUP);
	pinMode(joystickP2, INPUT_PULLUP);

	pinMode(tmpLed, OUTPUT);
	pinMode(tmpLedPWMX, OUTPUT);
	pinMode(tmpLedPWMY, OUTPUT);
}

void loop() {
	if (serialCommunication.commandReceived()) {
		// Print back command
		Serial.print("Command received:");
		for (int i = 0; i < serialCommunication.receivedCommandNumParts(); i++) {
			Serial.print(" '");
			Serial.print(serialCommunication.receivedCommandPart(i));
			Serial.print("'");
		}
		Serial.println();
	}

	// put your main code here, to run repeatedly:
	int pwmValueX = analogRead(joystickX);
	int pwmValueY = analogRead(joystickY);
	analogWrite(tmpLedPWMX, pwmValueX >> 2);
	analogWrite(tmpLedPWMY, pwmValueY >> 2);

	if ((digitalRead(joystickP1) == LOW) || (digitalRead(joystickP2) == LOW)) {
		digitalWrite(tmpLed, HIGH);
	} else {
		digitalWrite(tmpLed, LOW);
	}

	Serial.print(pwmValueX);
	Serial.print(" ");
	Serial.print(pwmValueY);
}
