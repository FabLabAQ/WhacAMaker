#include "serialCommunication.h"

SerialCommunication::SerialCommunication(QObject* parent) :
	QObject(parent),
	m_serialPort()
{
}

SerialCommunication::~SerialCommunication()
{
}
