TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += ../../pathfinding

win32 {
    CONFIG(debug, debug|release) {
        LIBS += -L"../../pathfinding/debug" -lpathfinding
    } else {
        LIBS += -L"../../pathfinding/release" -lpathfinding
    }
} else {
    LIBS += -L"../../pathfinding" -lpathfinding
}


MOC_DIR = .moc
OBJECTS_DIR = .obj
