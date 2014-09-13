#include <QGuiApplication>
#include <QQuickView>
#include <QObject>
#include <QQmlEngine>
#include "controller.h"
#include "gameItem.h"

int main(int argc, char *argv[])
{
	// Creating the application
	QGuiApplication app(argc, argv);

	// Registering the new QML types
	qmlRegisterType<GameItem>("TiroAlMostro", 1, 0, "GameItem");

	// Creating the view
	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:/qml/application.qml"));
	view.show();

	// Connecting the signal to quict the application when the QML engine terminates
	QObject::connect(view.engine(), SIGNAL(quit()), QGuiApplication::instance(), SLOT(quit()));

	// Creating the controller
	Controller controller(view);

	// Starting the application
	return app.exec();
}
