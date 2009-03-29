#include "testsamples.h"

#include <QtTest/QtTest>
#include "qtestext.h"

QTESTEXT_ADD_TO(TestSample1,first);
QTESTEXT_ADD_TO(TestSample2,testing);
QTESTEXT_ADD_TO(TestSample3,testing_sample);
QTESTEXT_ADD_TO(TestSample4,testing_sample_other);
QTESTEXT_ADD_TO(TestSample5,testing_sample_other);
QTESTEXT_ADD_TO(TestSample6,testing_sample_yetanother);

TestSample1::TestSample1()
{
}

void TestSample1::test1()
{
  QVERIFY(true);
}

void TestSample1::test2()
{
  QVERIFY(true);
}


TestSample2::TestSample2()
{
}

void TestSample2::test1()
{
  QVERIFY(true);
}

void TestSample2::test2()
{
  QVERIFY(true);
}



TestSample3::TestSample3()
{
}

void TestSample3::test1()
{
  QVERIFY(true);
}

void TestSample3::test2()
{
  QVERIFY(true);
}



TestSample4::TestSample4()
{
}

void TestSample4::test1()
{
  QVERIFY(true);
}

void TestSample4::test2()
{
  QVERIFY(true);
}



TestSample5::TestSample5()
{
}

void TestSample5::test1()
{
  QVERIFY(true);
}

void TestSample5::test2()
{
  QVERIFY(true);
}



TestSample6::TestSample6()
{
}

void TestSample6::test1()
{
  QVERIFY(true);
}

void TestSample6::test2()
{
  QVERIFY(true);
}

