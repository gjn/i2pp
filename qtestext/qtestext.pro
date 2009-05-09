#    this file is part of i2pp
#    Copyright (C)2009 Gilbert Jeiziner
#
#    This program is free software; you can redistribute it and/or
#    modify it under the terms of the GNU General Public License
#    as published by the Free Software Foundation; either
#    version 2 of the License, or (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

TEMPLATE = lib

QT += testlib
QT -= gui

CONFIG += staticlib

TARGET = qtestext

DESTDIR = lib

INCLUDEPATH += include

MOC_DIR = release
OBJECTS_DIR = release

CONFIG(debug, debug|release){
    TARGET = $$join(TARGET,,,D)
    DEFINES += DEBUG
    MOC_DIR = debug
    OBJECTS_DIR = debug
}

SOURCES += \
    src/testSuite.cpp \
    src/testNode.cpp
HEADERS += \
    include/qtestext.h \
    include/testFacade.h \
    include/testSuite.h \
    src/testNode.h
