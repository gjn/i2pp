/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#include "testSuite.h"
#include "testNode.h"
#include <QTest>

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
  _list += pTest;
}

int TestSuite::run(int argc, char* argv[])
{
  int result = 0;
  foreach(QObject* test, _list)
  {
    int temp = QTest::qExec(test, argc, argv);
    result |= temp;
  }
  return result;
}
