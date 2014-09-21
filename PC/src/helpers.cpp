#include "helpers.h"
#include <QQuickItem>
#include "myRuntimeException.h"

QObject* getQmlObject(QQuickView& view, const char* function)
{
	// Getting a reference to the QML object
	QVariant returnedObject;
	QMetaObject::invokeMethod(view.rootObject(), function, Q_RETURN_ARG(QVariant, returnedObject));
	QObject* const object = qvariant_cast<QObject *>(returnedObject);

	if (object == NULL) {
		throwMyRuntimeException(QString("Cannot access the object via the %1 QML function").arg(function));
	}

	return object;
}
