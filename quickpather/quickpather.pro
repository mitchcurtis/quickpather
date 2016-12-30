QT += quick

TARGET = quickpather
TEMPLATE = lib

DEFINES += QUICKPATHER_LIBRARY

HEADERS += \
    gametimer.h \
    quickentity.h \
    quickpather_global.h \
    gridpather.h \
    utils.h \
    gridpathnode.h \
    gridpathagent.h \
    steeringagent.h \
    passabilityagent.h \
    box2dkineticsteeringagent.h \
    directpather.h

SOURCES += \
    gametimer.cpp \
    quickentity.cpp \
    gridpather.cpp \
    gridpathnode.cpp \
    gridpathagent.cpp \
    steeringagent.cpp \
    passabilityagent.cpp \
    box2dkineticsteeringagent.cpp \
    directpather.cpp
