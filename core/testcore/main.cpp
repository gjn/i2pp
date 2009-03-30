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
#include "qtestext.h"
#include <iostream>

int main(int argc, char *argv[])
{
    int nresult = 0;
    int ncount = 0;
    int nDummy;
    //run all tests
    nresult += qtestext::TestSuite::getInstance()->run(nDummy,argc,argv);
    ncount += nDummy;
    std::cout  << "*************************************************************************" << std::endl;
    if (nresult > 0)
        std::cout << nresult << " Failure(s)! (" << ncount << " classes tested)" << std::endl;
    else
        std::cout << "0 Failures (" << ncount << " classes tested)" << std::endl;
    std::cout  << "*************************************************************************" << std::endl;
    return nresult;
}
