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
