#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "gametimer.h"
#include "gridpather.h"
#include "quickdirectpather.h"
#include "quickentity.h"

#include "hackypassabilityagent.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    using namespace QuickPather;

    qmlRegisterType<GameTimer>("QuickPather", 1, 0, "GameTimer");
    qmlRegisterType<DirectPather>("QuickPather", 1, 0, "DirectPather");
    qmlRegisterType<GridPather>("QuickPather", 1, 0, "GridPather");
    qmlRegisterType<QuickEntity>("QuickPather", 1, 0, "QuickEntity");

    qmlRegisterType<HackyPassabilityAgent>("Example", 1, 0, "HackyPassabilityAgent");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
