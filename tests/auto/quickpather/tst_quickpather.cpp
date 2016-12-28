#include <QString>
#include <QtTest>

#include "entity.h"
#include "gametimer.h"
#include "gridpather.h"

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
    QuickPather::GameTimer timer;

    QuickPather::GridPather pather;
    pather.setTimer(&timer);

    QuickPather::Entity entity;

    // Move from {0, 0} to {1, 0}
    entity.setCentrePos(QPointF(16, 16));
    QPointF pos(48, 16);
    QVERIFY(pather.moveEntityTo(&entity, pos));
    QCOMPARE(pather.pathData(&entity).nodes().size(), 1);
    // TODO: test steering as well
    pather.cancelEntityMovement(&entity);

    // Move from non-factor-of-cell-size position to {1, 0}
    entity.setCentrePos(QPointF(0, 0));
    QTest::ignoreMessage(QtWarningMsg, "Currently incapable of dealing with non-cell-centered positions");
    QVERIFY(!pather.moveEntityTo(&entity, pos));
    QCOMPARE(pather.pathData(&entity).nodes().size(), 0);
    // TODO: test steering as well
    pather.cancelEntityMovement(&entity);
}

QTEST_APPLESS_MAIN(tst_QuickPather)

#include "tst_quickpather.moc"
