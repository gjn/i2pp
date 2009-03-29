# -------------------------------------------------
# Project created by QtCreator 2009-03-28T16:03:05
# -------------------------------------------------
QT += testlib
QT -= gui
DESTDIR = lib
TARGET = qtestext
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += include
CONFIG(debug, debug|release){
    TARGET = qtestextD
    DEFINES += DEBUG
}
SOURCES += src/testSuite.cpp \
    src/testNode.cpp
HEADERS += include/qtestext.h \
    include/testFacade.h \
    include/testSuite.h \
    src/testNode.h
