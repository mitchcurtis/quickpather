QT += quick

TARGET = pathfinding
TEMPLATE = lib

DEFINES += PATHFINDING_LIBRARY

SOURCES += pathfinder.cpp

HEADERS += pathfinder.h \
        pathfinding_global.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
