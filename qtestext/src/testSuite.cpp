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

}
