#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "gametimer.h"
#include "directpather.h"
#include "quickentity.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameTimer>("QuickPath", 1, 0, "GameTimer");
    qmlRegisterType<DirectPather>("QuickPath", 1, 0, "DirectPathFinder");
    qmlRegisterType<QuickEntity>("QuickPath", 1, 0, "QuickEntity");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
