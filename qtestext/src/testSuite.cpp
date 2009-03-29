/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#include "testSuite.h"
#include "testNode.h"

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

int TestSuite::run(int argc, char* argv[])
{
  return _rootNode->run("*",argc,argv);
}

int TestSuite::run(QStringList& arguments)
{
  return _rootNode->run("*",arguments);
}

int TestSuite::run(QString hi, int argc, char* argv[])
{
  if (hi.isEmpty())
    return _rootNode->run("*", argc,argv);
  else
    return _rootNode->run(hi, argc,argv);
}

int TestSuite::run(QString hi, QStringList& arguments)
{
  if (hi.isEmpty())
    return _rootNode->run("*", arguments);
  else
    return _rootNode->run(hi, arguments);
}

