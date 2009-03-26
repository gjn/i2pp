# -------------------------------------------------
# Project created by QtCreator 2009-03-25T17:53:32
# -------------------------------------------------
QT += network
QT -= gui
TARGET = i2pp-router
TEMPLATE = lib
INCLUDEPATH += include \
    ../core/include
DEFINES += I2PP_ROUTER_LIBRARY
PRECOMPILED_HEADER = src/pc.h
SOURCES += src/router.cpp
HEADERS += include/router.h \
    include/router_global.h \
    src/pc.h
