#include "mainWindowEventFilter.h"
#include <QGuiApplication>
#include <QCursor>

namespace {
	// Useful constants: the time to wait before making the pointer disappear in milliseconds
	const int pointerTime = 1000;
}

MainWindowEventFilter::MainWindowEventFilter(QWindow* mainWindow)
	: QObject(NULL)
	, m_timer()
{
	// Connecting to the timer timeout signal
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));

	// Registering as the main window event filter
	mainWindow->installEventFilter(this);

	// Starting timer
	m_timer.start(pointerTime);
}

MainWindowEventFilter::~MainWindowEventFilter()
{
	// Nothing to do here
}

bool MainWindowEventFilter::eventFilter(QObject*, QEvent* event)
{
	if (dynamic_cast<QMouseEvent*>(event) != NULL) {
		if (QGuiApplication::overrideCursor() != NULL) {
			QGuiApplication::restoreOverrideCursor();
		}

		m_timer.start(pointerTime);
	}

	// We always let the system handle the event
	return false;
}

void MainWindowEventFilter::timeout()
{
	QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
}
