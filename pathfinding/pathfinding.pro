QT += quick

TARGET = pathfinding
TEMPLATE = lib

DEFINES += PATHFINDING_LIBRARY

SOURCES += pathfinder.cpp \
    gametimer.cpp

HEADERS += pathfinder.h \
        pathfinding_global.h \
    gametimer.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
