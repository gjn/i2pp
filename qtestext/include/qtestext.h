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

#ifndef QTESTEXT_H
#define QTESTEXT_H

/*!
  @mainpage

  qtestext is a simple extension to the Qt Test Module.
  It's heavily inspired (if not to say copied) from the
  QtTestUtil project at http://git.el-tramo.be/browse/qttestutil.git/
  by Remko Tronçon.

  It allows the registration of tests into a test suit.
  The tests are organized in a tree-like hierarchy in
  the suit. The tree of the suit can be executed as a whole,
  or only desired leaves.

  The tree is build using names. Each node of the tree can
  none, one or n tests.

  \section Usage
  Define your test classes as specified in the Qt Test Module
  documentation. Inside a cpp file, call the macro:

  @code
  QTESTEXT_ADDTO_SUITE(CMyTestClass,this_is_the_tree_node);
  @endcode

  where CMyTestClass is your test class to be executed, and
  this_is_the_tree_node describes on wich node in the tree the
  test will be placed. Do this for every TestClass that you want
  to include in the tree.
  \note the node name must be specified without quotes.

  A call to
  @code
  qtestext::TestSuite::getInstance()->run(...)
  @endcode
  executes the tests you want. It will return the number of
  TestClasses that were executed as well as the number of errors
  produced in this run.

  @code
  #include qtestext.h
  @endcode
  The above include should give you everything you need.

  \section Restrictions
  '_' is acting as a node separator. This is due to the fact that
  a static variable is created for each call to the macro, and the
  name of the macro will be derived from this specifier.
  This is also the reason that node-names can only contain characters
  that are allowed in variable names in C++.

  It is however allowed to add the same TestClass to different nodes
  on the tree. Also, it's allowed to add several TestClasses to the
  same node in the tree.

  \section Details
  Here is a more detailed sample:
  @code
  QTESTEXT_ADD_TO(TestSample1,first);
  QTESTEXT_ADD_TO(TestSample2,testing);
  QTESTEXT_ADD_TO(TestSample3,testing_sample);
  QTESTEXT_ADD_TO(TestSample4,testing_sample_other);
  QTESTEXT_ADD_TO(TestSample5,testing_sample_other);
  QTESTEXT_ADD_TO(TestSample6,testing_sample_yetanother);
  QTESTEXT_ADD_TO(TestSample2,"second"); is a valid definition.
  @endcode

  the following will trigger a compiler errors:
  @code
  //don't use quotes!
  QTESTEXT_ADD_TO(TestSampleXXX,"dummy");
  //don't add same test class to same tree node
  QTESTEXT_ADD_TO(TestSample2,"second");
  @endcode

  here is how you can run the above samples:
  @code
  int nrFailed = 0;
  int nrExecuted = 0;
  //run all tests
  nrFailed = TestSuite::getInstance()->run(nrExecuted, ...);

  //run all tests (other method)
  nrFailed = TestSuite::getInstance()->run("*", nrExecuted, ...);

  //run all tests (yet another possibility)
  nrFailed = TestSuite::getInstance()->run("", nrExecuted, ...);

  //will run TestSample1 only
  nrFailed = TestSuite::getInstance()->run("first", nrExecuted, ...);

  //will run TestSample2 only
  nrFailed = TestSuite::getInstance()->run("testing", ...);

  // will run TestSample2, TestSample3, ..., TestSample6
  nrFailed = TestSuite::getInstance()->run("testing_*", nrExecuted, ...);

  //will run TestSample3 only
  nrFailed = TestSuite::getInstance()->run("testing_sample", nrExecuted, ...);

  // will run TestSample3, TestSample4, ..., TestSample6
  nrFailed = TestSuite::getInstance()->run("testing_sample_*", ...);

  // will run TestSample4 and TestSample5
  nrFailed = TestSuite::getInstance()->run("testing_sample_other", nrExecuted, ...);
  @endcode

  A working sample can be found in the qtestextsample directory.

  \author Gilbert Jeiziner
  \version 0.0.1 (March 2009)
*/

#include "testFacade.h"
#include <QtTest/QtTest>

#define QTESTEXT_ADD_TO(TestClass,Hierarchy) static qtestext::TestFacade<TestClass> TestClass##Hierarchy(QString(#Hierarchy))

#endif // QTESTEXT_H
