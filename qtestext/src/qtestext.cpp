/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#include "qtestext.h"

void testfunc(int* pTest);
void testfunc(int* pTest)
{
  *pTest = 5;
}

QTESTEXT_ADD_TO(s,int);
