# -------------------------------------------------
# Project created by QtCreator 2009-03-28T21:13:00
# -------------------------------------------------
QT += testlib
QT -= gui
TARGET = runsamples
CONFIG += console
CONFIG -= app_bundle
LIBS += -L../lib/
CONFIG(release, debug|release){
    LIBS += -lqtestext
}
else{
    LIBS += -lqtestextD
    DEFINES += DEBUG
}
TEMPLATE = app
INCLUDEPATH = ../include
SOURCES += main.cpp \
    testsamples.cpp
HEADERS += testsamples.h
