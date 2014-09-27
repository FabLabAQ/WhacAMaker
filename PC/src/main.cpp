#include <QGuiApplication>
#include <QQuickView>
#include <QObject>
#include <QQmlEngine>
#include <QtQml>
#include <iostream>
#include <exception>
#include "controller.h"
#include "myRuntimeException.h"
#include "whackAMaker.h"

int main(int argc, char *argv[])
{
	try {
		// Creating the application
		QGuiApplication app(argc, argv);

		// Setting organization, domain and application names to be used by QSettings
		QGuiApplication::setOrganizationName("FabLab AQ");
		QGuiApplication::setOrganizationDomain("fablaquila.org");
		QGuiApplication::setApplicationName("Whack A Maker");

		// Registering the new QML types
		qmlRegisterType<WhackAMaker>("WhackAMaker", 1, 0, "WhackAMaker");

		// Creating the view
		QQuickView view;
		view.setResizeMode(QQuickView::SizeRootObjectToView);
		view.setSource(QUrl("qrc:///qml/application.qml"));
		view.show();

		// Connecting the signal to quict the application when the QML engine terminates
		QObject::connect(view.engine(), SIGNAL(quit()), QGuiApplication::instance(), SLOT(quit()));

		// Creating the controller
		Controller controller(view);

		// Starting the application
		return app.exec();
	} catch (MyRuntimeException& e) {
		std::cerr << "RUNTIME EXCEPTION, REASON: " << e.what() << std::endl;
	} catch (std::exception& e) {
		std::cerr << "GENERIC EXCEPTION, REASON: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "UNKNOWN EXCEPTION " << std::endl;
	}

	return 1;
}
