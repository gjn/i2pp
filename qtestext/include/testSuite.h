/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#ifndef QTESTEXT_TESTSUITE_H
#define QTESTEXT_TESTSUITE_H

#include <QObject>
#include <QString>
#include <QList>

namespace qtestext {

class TestNode;

class TestSuite
{
  public:
    static TestSuite* getInstance();

    TestSuite();
    ~TestSuite();

    //run all tests. See QTest::qExec function about the measing of these parameters
    //count returns the number of testclasses run.
    int run(int& count,int argc = 0, char* argv[] = 0);
    int run(int& count,QStringList& arguments);

    //run the tests for the given hierarchy as a first string parameter
    int run(QString hierarchy,int& count,int argc = 0, char* argv[] = 0);
    int run(QString hierarchy,int& count,QStringList& arguments);

    /*
      You should not use this function directly. Use the
      QTESTEXT_ADD_TO instead.
    */
    void addTest(QObject* pTest, QString hierarchy);

  private:
    TestNode* _rootNode;
};

}
#endif // QTESTEXT_TESTSUITE_H
