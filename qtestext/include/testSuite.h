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

namespace qtestext {

class TestNode;

class TestSuite
{
  public:
    static TestSuite* getInstance();

    TestSuite();
    ~TestSuite();

    void addTest(QObject* pTest, QString hierarchy);

  private:
    TestNode* _rootNode;
};

}

#endif // QTESTEXT_TESTSUITE_H
