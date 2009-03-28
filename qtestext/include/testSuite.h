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

    int run(int argc, char* argv[]);


    /*
      You should not use this function directly. Use the
      QTESTEXT_ADD_TO instead.
    */
    void addTest(QObject* pTest, QString hierarchy);

  private:
    TestNode* _rootNode;
    //for first tests...just put them in a list without hierarchy
    QList<QObject*> _list;
};

}
#endif // QTESTEXT_TESTSUITE_H
