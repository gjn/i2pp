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

#include "testrandom.h"
#include "util/random.h"
#include "context.h"
#include "qtestext.h"

#include <iostream>

QTESTEXT_ADD_TO(TestRandom,core_util);

TestRandom::TestRandom()
{
}

void TestRandom::testSimple()
{
    QByteArray ba(20,0);
    i2pp::core::Random* random = i2pp::core::Context::globalContext()->random();
    QVERIFY(random->getBytes(ba));
    QVERIFY(ba.size() == 20);
    QByteArray bb = ba;
    QVERIFY(random->getBytes(ba));
    QVERIFY(ba.size() == 20);
    QVERIFY(ba != bb);

    std::cout << "first created random bytes (base64 encoded): " << QString(bb.toBase64().data()).toStdString().c_str() << std::endl;
    std::cout << "second created random bytes (base64 encoded): " << QString(ba.toBase64().data()).toStdString().c_str() << std::endl;
}

