/*  this file is part of i2pp
    Copyright (C)2009 Gilbert Jeiziner

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifndef QTESTEXT_TESTSUITE_H
#define QTESTEXT_TESTSUITE_H

#include <QObject>
#include <QString>
#include <QList>

namespace qtestext
{

//forward declaration
class TestNode;

/*! TestSuite
  A testsuite is a singleton that will contain all added
  tests inside a tree.
*/
class TestSuite
{
    public:
        ///get the TestSuite singleton
        static TestSuite* getInstance();

        TestSuite();
        ~TestSuite();

        ///runs all tests. See other run functions for details.
        int run(int& count,int argc = 0, char* argv[] = 0);
        int run(int& count,QStringList& arguments);

        /*! Run tests
          @param hierarchy - String giving the tree node (and possibly children) to execute
          @param count - In/Out counts the number of tests that were run
          @param argc - Passed to QTest::qExec function (see Qt documentation for details)
          @param argv - Passed to QTest::qExec function (see Qt documentation for details)
          @return number of failures
        */
        int run(QString hierarchy,int& count,int argc = 0, char* argv[] = 0);
        int run(QString hierarchy,int& count,QStringList& arguments);

        /*! adding tests to a suite.
          @note You should not use this function directly. Use the macro defined in
          the qtestext.h header instead.
        */
        void addTest(QObject* pTest, QString hierarchy);

    private:
        TestNode* _rootNode;
};

}
#endif // QTESTEXT_TESTSUITE_H
