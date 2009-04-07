/*  this file is part of i2pp
    Copyright (C)2009 Gilbert Jeiziner

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "testsystemtime.h"
#include "time/systemtime.h"
#include "qtestext.h"

#include <iostream>

QTESTEXT_ADD_TO(TestSystemTime,core_time);

TestSystemTime::TestSystemTime()
{
}

void TestSystemTime::testMax()
{
    QDateTime max = i2pp::core::SystemTime::maxDate();
    std::cout << "Max i2pp time = " << qPrintable(max.toString("yyyy-MM-dd hh::mm::ss")) << std::endl;
    //if this one below fails, it is very likely that the times currently
    //provided by i2pp::core::time class are out of range!
    QVERIFY(QDateTime::currentDateTime() < max);
}

