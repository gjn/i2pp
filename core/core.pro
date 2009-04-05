# this file is part of i2pp
# Copyright (C)2009 Gilbert Jeiziner
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
TEMPLATE = lib
QT += network
QT -= gui
CONFIG += staticlib
TARGET = i2pp-core
DESTDIR = lib
INCLUDEPATH += \
    include \
    include/time \
    include/util \
    src \
    ../log4qt/src

LIBS += -lcryptopp

PRECOMPILED_HEADER = src/pc.h
CONFIG(debug, debug|release) { 
    TARGET = $$join(TARGET,,,D)
    DEFINES += DEBUG
}
win32:DEFINES += WIN32
include(../log4qt/src/log4qt/log4qt.pri)
include(./src/time/time.pri)
include(./src/util/util.pri)

SOURCES += src/context.cpp

HEADERS += \
    src/pc.h \
    include/context.h \
    include/core.h \
