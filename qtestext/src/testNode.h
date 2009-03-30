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
#ifndef QTESTEXT_TESTNODE_H
#define QTESTEXT_TESTNODE_H

#include <QMap>
#include <QList>
#include <QString>
#include <QObject>

namespace qtestext
{

class TestNode
{
    public:
        TestNode();

        static int _count;

        void addTestToNode(QObject*,QString);

        int run(QString hierarchy, bool mainstyle, int argc, char* argv[],
                QStringList& arguments);
    protected:
        void setName(QString str);
        QString _name;
        ///the tests of this node
        QList<QObject*> _tests;
        ///the child nodes of this node
        QMap<QString,TestNode> _children;
};

} //namespace qtestext

#endif // QTESTEXT_TESTNODE_H
