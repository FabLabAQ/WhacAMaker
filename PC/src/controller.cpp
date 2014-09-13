#include "controller.h"
#include <QQuickItem>
#include <iostream>

Controller::Controller(QQuickView& view, QObject* parent) :
	QObject(parent),
	m_view(view)
{
	// Connecting signals from m_view to our slots
	connect(m_view.rootObject(), SIGNAL(configurationParametersSaved(QVariant)), this, SLOT(saveConfigurationParameters(QVariant))); //<------ QUESTA NON FUNZIONA, VEDERE PERCHÈ
	connect(m_view.rootObject(), SIGNAL(playerNameEntered(QString)), this, SLOT(savePlayerName(QString)));
}

Controller::~Controller()
{
	// Nothing to do here
}

void Controller::saveConfigurationParameters(const QVariant& obj)
{
	std::cerr << "SAVED CONFIGURATION" << std::endl;
}

void Controller::savePlayerName(const QString& name)
{
	std::cerr << "Player name: " << name.toLatin1().data() << std::endl;
}
