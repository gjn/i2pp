/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
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

