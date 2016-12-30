#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "gametimer.h"
#include "gridpather.h"
#include "directpather.h"
#include "quickentity.h"
#include "box2dkineticsteeringagent.h"

#include "box2dpassabilityagent.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    using namespace QuickPather;

    qmlRegisterType<GameTimer>("QuickPather", 1, 0, "GameTimer");
    qmlRegisterType<DirectPather>("QuickPather", 1, 0, "DirectPather");
    qmlRegisterType<GridPather>("QuickPather", 1, 0, "GridPather");
    qmlRegisterType<QuickEntity>("QuickPather", 1, 0, "QuickEntity");
    qmlRegisterType<PassabilityAgent>("QuickPather", 1, 0, "PassabilityAgent");
    qmlRegisterType<SteeringAgent>("QuickPather", 1, 0, "SteeringAgent");
    qmlRegisterType<Box2DKineticSteeringAgent>("QuickPather", 1, 0, "Box2DKineticSteeringAgent");

    qmlRegisterType<Box2DPassabilityAgent>("Example", 1, 0, "Box2DPassabilityAgent");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
