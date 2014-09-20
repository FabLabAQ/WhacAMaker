#include "joystick.h"
#include "Arduino.h"

Joystick::Joystick() :
	m_pinP1(0),
	m_pinP2(0),
	m_pinX(0),
	m_pinY(0),
	m_button1Pressed(false),
	m_button2Pressed(false),
	m_xPosition(512),
	m_yPosition(512)
{
}

void Joystick::begin(int p1, int p2, int x, int y)
{
	// Copying pins
	m_pinP1 = p1;
	m_pinP2 = p2;
	m_pinX = x;
	m_pinY = y;

	// Initialize pins
	pinMode(m_pinP1, INPUT_PULLUP);
	pinMode(m_pinP2, INPUT_PULLUP);
}

void Joystick::readStatus()
{
	// Reading the status of axes and buttons
	m_button1Pressed = (digitalRead(m_pinP1) == LOW);
	m_button2Pressed = (digitalRead(m_pinP2) == LOW);
	m_xPosition = analogRead(m_pinX);
	m_yPosition = analogRead(m_pinY);
}
