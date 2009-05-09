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

QT += network
QT -= gui

TARGET = i2pp-router

DESTDIR = lib

INCLUDEPATH += include \
    ../core/include

DEFINES += I2PP_ROUTER_LIBRARY

MOC_DIR = release
OBJECTS_DIR = release

LIBS += -L../core/lib/
CONFIG(release, debug|release){
    LIBS += -li2pp-core
}
else{
    DEFINES += DEBUG
    LIBS += -li2pp-coreD
    TARGET = i2pp-routerD
    MOC_DIR = debug
    OBJECTS_DIR = debug

}

PRECOMPILED_HEADER = src/pc.h

SOURCES += src/router.cpp

HEADERS += include/router.h \
    include/router_global.h \
    src/pc.h
