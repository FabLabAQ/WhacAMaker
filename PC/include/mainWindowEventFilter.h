#ifndef __MAIN_WINDOW_EVENT_FILTER_H__
#define __MAIN_WINDOW_EVENT_FILTER_H__

#include <QObject>
#include <QMouseEvent>
#include <QWindow>
#include <QTimer>

/**
 * \brief The object installed as event filter of the main window
 *
 * This is used to hide the mouse cursor when not moved
 */
class MainWindowEventFilter : public QObject
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor
	 *
	 * \param mainWindow the main window. We become its event filter
	 */
	MainWindowEventFilter(QWindow* mainWindow);

	/**
	 * \brief Destructor
	 */
	virtual ~MainWindowEventFilter();

	/**
	 * \brief The function receiving the event from the main window
	 *
	 * \param watched the object whose events we receive
	 * \param event the event
	 */
	virtual bool eventFilter(QObject* watched, QEvent* event);

private slots:
	/**
	 * \brief The timer timeout
	 */
	void timeout();

private:
	/**
	 * \brief The timer we use to hide the pointer
	 */
	QTimer m_timer;
};

#endif
