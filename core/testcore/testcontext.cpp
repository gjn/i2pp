#include "testcontext.h"
#include "context.h"
#include "qtestext.h"

QTESTEXT_ADD_TO(TestContext,core);

TestContext::TestContext()
{
}

void TestContext::testConstruction()
{
  i2pp::core::Context newContext;
  QCOMPARE(newContext.name(),QString("default"));
  i2pp::core::Context anotherContext("testing");
  QCOMPARE(anotherContext.name(),QString("testing"));
}

void TestContext::testLogger()
{
  i2pp::core::Context context("testing");
  LOG4CXX_DEBUG(context.logger("my.first.logger"),"this is my first log message");
}
