#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "pathfinder.h"
#include "gametimer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PathFinder>("QuickPath", 1, 0, "PathFinder");
    qmlRegisterType<GameTimer>("QuickPath", 1, 0, "GameTimer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
