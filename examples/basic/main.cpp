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

    using namespace QuickPather;

    qmlRegisterType<GameTimer>("QuickPath", 1, 0, "GameTimer");
    qmlRegisterType<QuickDirectPather>("QuickPath", 1, 0, "QuickDirectPather");
    qmlRegisterType<QuickGridPather>("QuickPath", 1, 0, "QuickGridPather");
    qmlRegisterType<QuickEntity>("QuickPath", 1, 0, "QuickEntity");

    qmlRegisterType<HackyPassabilityAgent>("Example", 1, 0, "HackyPassabilityAgent");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
