TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += ../../quickpather

win32 {
    CONFIG(debug, debug|release) {
        LIBS += -L"../../quickpather/debug" -lquickpather
    } else {
        LIBS += -L"../../quickpather/release" -lquickpather
    }
} else {
    LIBS += -L"../../quickpather" -lquickpather
}

MOC_DIR = .moc
OBJECTS_DIR = .obj
