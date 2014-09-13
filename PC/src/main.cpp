#include <QGuiApplication>
#include <QQuickView>
#include <QObject>
#include <QQmlEngine>
#include "gameItem.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<GameItem>("TiroAlMostro", 1, 0, "GameItem");

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:/qml/application.qml"));
	view.show();

	QObject::connect(view.engine(), SIGNAL(quit()), QGuiApplication::instance(), SLOT(quit()));

	return app.exec();
}
