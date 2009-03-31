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

#include "runner.h"
#include "qtestext.h"
#include <iostream>

Runner::Runner(QCoreApplication* pApp):
_pApplication(pApp),
_retVal(0)
{
}

void Runner::run()
{
    //make sure we stop the application when we are finished
    Exiter exit(_pApplication);

    _retVal = 0;
    int ncount = 0;
    int nDummy;
    //run all tests
    QStringList args = QCoreApplication::arguments();
    _retVal += qtestext::TestSuite::getInstance()->run(nDummy,args);
    ncount += nDummy;
    std::cout  << "*************************************************************************" << std::endl;
    if (_retVal > 0)
        std::cout << _retVal << " Failure(s)! (" << ncount << " classes tested)" << std::endl;
    else
        std::cout << "0 Failures (" << ncount << " classes tested)" << std::endl;
    std::cout  << "*************************************************************************" << std::endl;
}

int Runner::getRetVal()
{
    return _retVal;
}

Exiter::Exiter(QCoreApplication* pApp):
_pApplication(pApp)
{
}

Exiter::~Exiter()
{
    _pApplication->exit();
}
