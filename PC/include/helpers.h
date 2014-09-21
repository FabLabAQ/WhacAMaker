#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <QObject>
#include <QQuickView>

/**
 * \brief Returns a pointer to the QML object using the given QML function
 *
 * This calls the QML function whith the given name that returns a pointer to a
 * QML object and takes no parameters
 * \param view the QML viewer
 * \param function the function to call
 * \return a pointer to the QML object
 */
QObject* getQmlObject(QQuickView& view, const char* function);

#endif

