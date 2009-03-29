/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#include "testNode.h"

#include <QStringList>
#include <QTest>

using namespace qtestext;

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
    _list += pTest;
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

int TestNode::run(QString hierarchy, int argc, char* argv[])
{
  QStringList bla;
  return run(hierarchy,true,argc,argv,bla);
}

int TestNode::run(QString hierarchy, QStringList& arguments)
{
  return run(hierarchy,false,0,NULL,arguments);
}

int TestNode::run(QString hierarchy, bool mainstyle, int argc, char* argv[], QStringList& arguments)
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
      if ((nodeNames.size() == 1 || (nodeNames.size() == 2 && nodeNames.at(1) == "*")) &&
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
    foreach(QObject* test, _list)
    {
      if (mainstyle)
        result += QTest::qExec(test, argc, argv);
      else
        result += QTest::qExec(test, arguments);
    }
  }
  return result;
}
