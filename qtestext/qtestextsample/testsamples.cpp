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
#include "testsamples.h"
#include "qtestext.h"

QTESTEXT_ADD_TO(TestSample1,first);
QTESTEXT_ADD_TO(TestSample2,testing);
QTESTEXT_ADD_TO(TestSample3,testing_sample);
QTESTEXT_ADD_TO(TestSample4,testing_sample_other);
QTESTEXT_ADD_TO(TestSample5,testing_sample_other);
QTESTEXT_ADD_TO(TestSample6,testing_sample_yetanother);

TestSample1::TestSample1()
{
}

void TestSample1::test1()
{
    QVERIFY(true);
}

void TestSample1::test2()
{
    QVERIFY(true);
}


TestSample2::TestSample2()
{
}

void TestSample2::test1()
{
    QVERIFY(true);
}

void TestSample2::test2()
{
    QVERIFY(true);
}



TestSample3::TestSample3()
{
}

void TestSample3::test1()
{
    QVERIFY(true);
}

void TestSample3::test2()
{
    QVERIFY(true);
}



TestSample4::TestSample4()
{
}

void TestSample4::test1()
{

    QVERIFY(true);
}

void TestSample4::test2()
{
    QVERIFY(true);
}



TestSample5::TestSample5()
{
}

void TestSample5::test1()
{
    QVERIFY(true);
}

void TestSample5::test2()
{
    QVERIFY(true);
}



TestSample6::TestSample6()
{
}

void TestSample6::test1()
{
    QVERIFY(true);
}

void TestSample6::test2()
{
    QVERIFY(true);
}

