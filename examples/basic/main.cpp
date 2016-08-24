#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "gametimer.h"
#include "quickdirectpather.h"
#include "quickentity.h"
#include "quickgridpather.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameTimer>("QuickPath", 1, 0, "GameTimer");
    qmlRegisterType<QuickDirectPather>("QuickPath", 1, 0, "QuickDirectPather");
    qmlRegisterType<QuickGridPather>("QuickPath", 1, 0, "QuickGridPather");
    qmlRegisterType<QuickEntity>("QuickPath", 1, 0, "QuickEntity");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
