#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "gametimer.h"
#include "quickdirectpather.h"
#include "quickentity.h"
#include "quickgridpather.h"

#include "hackypassabilityagent.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameTimer>("QuickPather", 1, 0, "GameTimer");
    qmlRegisterType<QuickDirectPather>("QuickPather", 1, 0, "QuickDirectPather");
    qmlRegisterType<QuickGridPather>("QuickPather", 1, 0, "QuickGridPather");
    qmlRegisterType<QuickEntity>("QuickPather", 1, 0, "QuickEntity");

    qmlRegisterType<HackyPassabilityAgent>("Example", 1, 0, "HackyPassabilityAgent");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
