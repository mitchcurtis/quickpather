#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "pathfinder.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PathFinder>("QuickPath", 1, 0, "PathFinder");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
