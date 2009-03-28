/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#ifndef QTESTEXT_TESTFACADE_H
#define QTESTEXT_TESTFACADE_H

#include "testSuite.h"

#include <QString>

namespace qtestext {

/*
  A facade encapsulating a Test class. This class shouldn't be used
  directly.
  Use the QTESTEXT_ADD_TO to add tests to the global test suite.
*/

template<class T>
class TestFacade
{
  public:
    TestFacade(QString hierarchy)
    {
      _test = new T;
      TestSuite::getInstance()->addTest(_test, hierarchy);
    };

    ~TestFacade()
    {
      delete _test;
    };

  private:
    T* _test;
};


} //namespace qtestext

#endif // QTESTEXT_TESTFACADE_H
