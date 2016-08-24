QT += testlib
QT -= gui

TARGET = tst_quickpather
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../quickpather

win32 {
    CONFIG(debug, debug|release) {
        LIBS += -L"../../../quickpather/debug" -lquickpather
    } else {
        LIBS += -L"../../../quickpather/release" -lquickpather
    }
} else {
    LIBS += -L"../../../quickpather" -lquickpather
}

SOURCES += tst_quickpather.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
