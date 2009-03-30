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
#include "testNode.h"

#include <QStringList>
#include <QTest>

using namespace qtestext;

int TestNode::_count = 0;

TestNode::TestNode()
{
}

void TestNode::setName(QString str)
{
    _name = str;
}

void TestNode::addTestToNode(QObject* pTest,QString hierarchy)
{
    QStringList nodeNames = hierarchy.split("_",QString::SkipEmptyParts);
    //if hierarchy is empty or no more hierarchy, we reached our node
    if (hierarchy.isEmpty() || nodeNames.isEmpty())
    {
        _tests += pTest;
    }
    else
    {
        //check if the node exists
        QString firstNode = nodeNames.at(0);
        if (!_children.contains(firstNode))
        {
            _children[firstNode].setName(firstNode);
        }

        nodeNames.removeFirst();
        QString newH="";
        bool bFirst = true;
        foreach(QString str, nodeNames)
        {
            if (!bFirst)
                newH += "_";
            newH += str;
            bFirst = false;
        }
        _children[firstNode].addTestToNode(pTest,newH);
    }
}

int TestNode::run(QString hierarchy, bool mainstyle, int argc, char* argv[],
                  QStringList& arguments)
{
    int result = 0;
    bool bCallOwn = false;
    if (hierarchy == "*" || _name.isEmpty())
    {
        QList<QString> keys = _children.keys();
        foreach(QString key, keys)
        {
            result += _children[key].run(hierarchy,mainstyle,argc,argv,arguments);
        }
        bCallOwn = (hierarchy == "*");
    }
    else
    {
        //let's check if we have to execute our tests
        QStringList nodeNames = hierarchy.split("_",QString::SkipEmptyParts);
        if (!nodeNames.isEmpty())
        {
            if ((nodeNames.size() == 1 ||
                (nodeNames.size() == 2 && nodeNames.at(1) == "*")) &&
                nodeNames.at(0) == _name)
                bCallOwn = true;

            if (nodeNames.size() > 1)
            {
                nodeNames.removeFirst();
                QString newH="";
                bool bFirst = true;
                foreach(QString str, nodeNames)
                {
                    if (!bFirst)
                        newH += "_";
                    newH += str;
                    bFirst = false;
                }
                QList<QString> keys = _children.keys();
                foreach(QString key, keys)
                {
                    result += _children[key].run(newH,mainstyle,argc,argv,arguments);
                }
            }

        }
    }
    if (bCallOwn)
    {
        foreach(QObject* test, _tests)
        {
            ++_count;
            if (mainstyle)
                result += QTest::qExec(test, argc, argv);
            else
                result += QTest::qExec(test, arguments);
        }
    }
    return result;
}
