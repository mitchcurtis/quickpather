QT += quick

TARGET = pathfinding
TEMPLATE = lib

DEFINES += PATHFINDING_LIBRARY

SOURCES += \
    gametimer.cpp \
    quickentity.cpp \
    directpathfinder.cpp

HEADERS += \
        pathfinding_global.h \
    gametimer.h \
    mathutils.h \
    quickentity.h \
    directpathfinder.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
