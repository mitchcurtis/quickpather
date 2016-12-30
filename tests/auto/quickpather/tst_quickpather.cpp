#include <QString>
#include <QtTest>

#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>

#include "gametimer.h"
#include "gridpather.h"
#include "gridpather.h"
#include "quickentity.h"
#include "passabilityagent.h"
#include "steeringagent.h"

class FreePassabilityAgent : public QuickPather::PassabilityAgent
{
public:
    FreePassabilityAgent() {}

    virtual bool isPassable(const QPointF &, QuickPather::QuickEntity *) override {
        return true;
    }
};

class tst_QuickPather : public QObject
{
    Q_OBJECT

public:
    tst_QuickPather();

private Q_SLOTS:
    void gridPather();
    void customQmlPassabilityAgent();
};

tst_QuickPather::tst_QuickPather()
{
}

void tst_QuickPather::gridPather()
{
    QuickPather::GridPather pather;
    // Try to move a null entity.
    QTest::ignoreMessage(QtWarningMsg, "GridPather: entity cannot be null");
    QVERIFY(!pather.moveEntityTo(nullptr, QPointF()));

    QuickPather::QuickEntity entity;
    QScopedPointer<QQuickItem> item(new QQuickItem);
    entity.setItem(item.data());

    // Try to move without setting a passability agent.
    QTest::ignoreMessage(QtWarningMsg, "GridPather: no timer set");
    entity.setCentrePos(QPointF(16, 16));
    QPointF pos(48, 16);
    QVERIFY(!pather.moveEntityTo(&entity, pos));

    QuickPather::GameTimer timer;
    pather.setTimer(&timer);

    // Try to move without setting a passability agent.
    QTest::ignoreMessage(QtWarningMsg, "GridPather: no passability agent set");
    QVERIFY(!pather.moveEntityTo(&entity, pos));

    FreePassabilityAgent passabilityAgent;
    pather.setPassabilityAgent(&passabilityAgent);

    // Try to move without setting a steering agent.
    QTest::ignoreMessage(QtWarningMsg, "GridPather: no steering agent set");
    QVERIFY(!pather.moveEntityTo(&entity, pos));

    QuickPather::SteeringAgent steeringAgent;
    pather.setSteeringAgent(&steeringAgent);

    // Move from {0, 0} to {1, 0}
    QVERIFY(pather.moveEntityTo(&entity, pos));
    QCOMPARE(pather.pathData(&entity).nodes().size(), 1);
    // TODO: test steering as well
    pather.cancelEntityMovement(&entity);

    // Move from non-factor-of-cell-size position to {1, 0}
    entity.setCentrePos(QPointF(0, 0));
    QTest::ignoreMessage(QtWarningMsg, QRegularExpression("GridPather: currently incapable of dealing with non-cell-centered positions.*"));
    QVERIFY(!pather.moveEntityTo(&entity, pos));
    QCOMPARE(pather.pathData(&entity).nodes().size(), 0);
    // TODO: test steering as well
    pather.cancelEntityMovement(&entity);
}

void tst_QuickPather::customQmlPassabilityAgent()
{
    QQmlEngine engine;

    // Check that our QML types can be assigned to our properties.
    qmlRegisterType<QuickPather::GameTimer>("QuickPather", 1, 0, "GameTimer");
    qmlRegisterType<QuickPather::GridPather>("QuickPather", 1, 0, "GridPather");
    qmlRegisterType<QuickPather::GridPather>("QuickPather", 1, 0, "QuickGridPather");
    qmlRegisterType<QuickPather::PassabilityAgent>("QuickPather", 1, 0, "PassabilityAgent");
    qRegisterMetaType<QuickPather::PassabilityAgent*>("PassabilityAgent");

    qmlRegisterType<FreePassabilityAgent>("Test", 1, 0, "FreePassabilityAgent");

    QQmlComponent component(&engine);
    component.setData(
        "import QtQuick 2.0 \n"
        "import QuickPather 1.0 \n"
        "import Test 1.0\n"
        "Item {"
            "GameTimer { \n"
                "id: gameTimer \n"
            "} \n"
            "QuickGridPather { \n"
                "id: gridPather \n"
                "timer: gameTimer \n"
                "passabilityAgent: freePassabilityAgent \n"
            "} \n"
            "FreePassabilityAgent { \n"
                "id: freePassabilityAgent \n"
            "} \n"
        "} \n", QUrl());

    QObject *root = component.create();
    QVERIFY2(root, qPrintable(component.errorString()));
}

QTEST_MAIN(tst_QuickPather)

#include "tst_quickpather.moc"
