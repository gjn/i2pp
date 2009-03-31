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

#include "testcontext.h"
#include "context.h"
#include "qtestext.h"

#include "log4qt/fileappender.h"


QTESTEXT_ADD_TO(TestContext,core);

TestContext::TestContext()
{
}

void TestContext::testConstruction()
{
    i2pp::core::Context newContext;
    QCOMPARE(newContext.name(),QString("global"));
    i2pp::core::Context anotherContext("t1");
    QCOMPARE(anotherContext.name(),QString("t1"));
    i2pp::core::Context sameNameContext("t1"); //this should put out error in log
    QCOMPARE(anotherContext.name(),QString("t1"));
}

void TestContext::testLogger()
{
    //we write to fatal, so we assure that it gets written
    i2pp::core::Context context("t1");
    Log4Qt::Logger* logger = context.logger("");
    QList<Log4Qt::Appender*> list=logger->appenders();
    QCOMPARE(list.size(),1);
    Log4Qt::FileAppender* pAppender = static_cast<Log4Qt::FileAppender*>(logger->appender("FileAppender"));
    QVERIFY(pAppender);
    QFileInfo fi(pAppender->file());
    qint64 nSize = 0;
    if (fi.exists())
        nSize = fi.size();
    context.logger("")->fatal("log message to test");
    fi=QFileInfo(pAppender->file());
    QVERIFY(fi.exists());
    qint64 nNewSize = fi.size();
    QVERIFY(nNewSize > nSize);
    nSize = nNewSize;
    //now, if we log with different logger from same context, it should be written
    //to same file
    context.logger("dummy")->fatal("is this writing to the same file?");
    fi=QFileInfo(pAppender->file());
    nNewSize = fi.size();
    QVERIFY(nNewSize > nSize);
}

void TestContext::testSettings()
{
    i2pp::core::Context context("t1");
    context.getSetting("dummykey",QString("dummyvalue"));
}
