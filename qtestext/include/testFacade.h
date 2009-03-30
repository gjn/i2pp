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
#ifndef QTESTEXT_TESTFACADE_H
#define QTESTEXT_TESTFACADE_H

#include "testSuite.h"

#include <QString>

namespace qtestext
{

/*! A facade encapsulating a real Test class.
  @note This class shouldn't be used directly. Use the
  macroe defined in qtestext.h header file instead
*/

template<class T>
class TestFacade
{
    public:
        TestFacade(QString hierarchy)
        {
            _test = new T;
            TestSuite::getInstance()->addTest(_test, hierarchy);
        }

        ~TestFacade()
        {
            delete _test;
        }

    private:
        T* _test;
};


} //namespace qtestext

#endif // QTESTEXT_TESTFACADE_H
