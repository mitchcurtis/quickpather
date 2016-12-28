#include <QString>
#include <QtTest>

#include "entity.h"
#include "gametimer.h"
#include "gridpather.h"
#include "quickgridpather.h"
#include "passabilityagent.h"

class FreePassabilityAgent : public QuickPather::PassabilityAgent
{
public:
    FreePassabilityAgent() {}

    virtual bool isPassable(const QPointF &, QuickPather::AbstractEntity *) override {
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
};

tst_QuickPather::tst_QuickPather()
{
}

void tst_QuickPather::gridPather()
{
    QuickPather::GridPather pather;
    QuickPather::Entity entity;

    // Try to move without setting a passability agent.
    QTest::ignoreMessage(QtWarningMsg, "GridPather: No timer set");
    entity.setCentrePos(QPointF(16, 16));
    QPointF pos(48, 16);
    QVERIFY(!pather.moveEntityTo(&entity, pos));

    QuickPather::GameTimer timer;
    pather.setTimer(&timer);

    // Try to move without setting a passability agent.
    QTest::ignoreMessage(QtWarningMsg, "GridPather: No passability agent set");
    QVERIFY(!pather.moveEntityTo(&entity, pos));

    FreePassabilityAgent passabilityAgent;
    pather.setPassabilityAgent(&passabilityAgent);

    // Move from {0, 0} to {1, 0}
    QVERIFY(pather.moveEntityTo(&entity, pos));
    QCOMPARE(pather.pathData(&entity).nodes().size(), 1);
    // TODO: test steering as well
    pather.cancelEntityMovement(&entity);

    // Move from non-factor-of-cell-size position to {1, 0}
    entity.setCentrePos(QPointF(0, 0));
    QTest::ignoreMessage(QtWarningMsg, QRegularExpression("GridPather: Currently incapable of dealing with non-cell-centered positions.*"));
    QVERIFY(!pather.moveEntityTo(&entity, pos));
    QCOMPARE(pather.pathData(&entity).nodes().size(), 0);
    // TODO: test steering as well
    pather.cancelEntityMovement(&entity);
}

QTEST_APPLESS_MAIN(tst_QuickPather)

#include "tst_quickpather.moc"
