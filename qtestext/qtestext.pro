# -------------------------------------------------
# Project created by QtCreator 2009-03-28T16:03:05
# -------------------------------------------------
QT += testlib
QT -= gui
TARGET = qtestext
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += include
SOURCES += src/qtestext.cpp \
    src/testSuite.cpp \
    src/testNode.cpp
HEADERS += include/qtestext.h \
    include/testFacade.h \
    include/testSuite.h \
    src/testNode.h