# -------------------------------------------------
# Project created by QtCreator 2009-03-29T15:37:52
# -------------------------------------------------
QT += testlib
QT -= gui
TARGET = testcore
CONFIG += console
CONFIG -= app_bundle
INCLUDEPATH += ../include \
    ../../qtestext/include
TEMPLATE = app
LIBS += -L../lib/ \
    -L../../qtestext/lib/
CONFIG(release, debug|release):LIBS += -lqtestext \
    -li2pp-core
else { 
    LIBS += -lqtestextD \
        -li2pp-coreD
    DEFINES += DEBUG
}
SOURCES += main.cpp \
    testcontext.cpp

# at the end, run the tests. so building failes when test is _not_ successfull
QMAKE_POST_LINK = ./testcore
HEADERS += testcontext.h
