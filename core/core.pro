# -------------------------------------------------
# Project created by QtCreator 2009-03-25T17:48:10
# -------------------------------------------------
QT += network
QT -= gui
TARGET = i2pp-core
TEMPLATE = lib
DESTDIR = lib
CONFIG += staticlib
INCLUDEPATH += include \
    src
PRECOMPILED_HEADER = src/pc.h
CONFIG(debug, debug|release){
    TARGET = i2pp-coreD
    DEFINES += DEBUG
}
SOURCES += src/context.cpp \
    src/time/ntpmessage.cpp
HEADERS += include/context.h \
    src/pc.h \
    include/core.h \
    src/time/ntpmessage.h

win32 {
    DEFINES += WIN32
}
