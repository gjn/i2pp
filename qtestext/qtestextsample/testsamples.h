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
#ifndef TESTSAMPLE1_H
#define TESTSAMPLE1_H

#include <QObject>

class TestSample1 : public QObject
{
    Q_OBJECT
    public:
        TestSample1();
    private slots:
        void test1();
        void test2();
};

class TestSample2 : public QObject
{
    Q_OBJECT
    public:
        TestSample2();
    private slots:
        void test1();
        void test2();
};

class TestSample3 : public QObject
{
    Q_OBJECT
    public:
        TestSample3();
    private slots:
        void test1();
        void test2();
};


class TestSample4 : public QObject
{
    Q_OBJECT
    public:
        TestSample4();
    private slots:
        void test1();
        void test2();
};

class TestSample5 : public QObject
{
    Q_OBJECT
    public:
        TestSample5();
    private slots:
        void test1();
        void test2();
};

class TestSample6 : public QObject
{
    Q_OBJECT
    public:
        TestSample6();
    private slots:
        void test1();
        void test2();
};

#endif // TESTSAMPLE1_H
