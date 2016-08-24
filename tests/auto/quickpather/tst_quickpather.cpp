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
    GameTimer timer;

    GridPather pather;
    pather.setTimer(&timer);

    Entity entity;
    entity.setCentrePos(QPointF(16, 16));

    QPointF pos(32, 0);
    pather.moveEntityTo(&entity, pos);
}

QTEST_APPLESS_MAIN(tst_QuickPather)

#include "tst_quickpather.moc"
