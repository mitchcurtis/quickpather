QT += quick

TARGET = quickpather
TEMPLATE = lib

DEFINES += QUICKPATHER_LIBRARY

SOURCES += \
    gametimer.cpp \
    quickentity.cpp \
    directpather.cpp

HEADERS += \
    gametimer.h \
    mathutils.h \
    quickentity.h \
    directpather.h \
    quickpather_global.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
