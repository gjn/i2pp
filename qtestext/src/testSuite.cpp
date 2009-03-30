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
#include "testSuite.h"
#include "testNode.h"
#include <QStringList>

using namespace qtestext;

TestSuite* TestSuite::getInstance()
{
    static TestSuite singleton;
    return &singleton;
}

TestSuite::TestSuite()
{
    _rootNode = new TestNode();
}

TestSuite::~TestSuite()
{
    delete _rootNode;
}

void TestSuite::addTest(QObject* pTest, QString hierarchy)
{
    _rootNode->addTestToNode(pTest,hierarchy);
}

int TestSuite::run(int& count, int argc, char* argv[])
{
    return run("*",count,argc,argv);
}

int TestSuite::run(int& count,QStringList& arguments)
{
    return run("*",count,arguments);
}

int TestSuite::run(QString hi, int& count, int argc, char* argv[])
{
    if (hi.isEmpty())
        hi = "*";
    TestNode::_count = 0;
    QStringList dummy;
    int nRetVal = _rootNode->run(hi,true,argc,argv,dummy);
    count = TestNode::_count;
    return nRetVal;
}

int TestSuite::run(QString hi, int& count, QStringList& arguments)
{
    if (hi.isEmpty())
        hi = "*";
    TestNode::_count = 0;
    int nRetVal = _rootNode->run(hi,false,0,NULL,arguments);
    count = TestNode::_count;
    return nRetVal;
}

