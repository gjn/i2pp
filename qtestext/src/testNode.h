/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#ifndef QTESTEXT_TESTNODE_H
#define QTESTEXT_TESTNODE_H

#include <QMap>
#include <QList>
#include <QString>
#include <QObject>

namespace qtestext {

class TestNode
{
  public:
    TestNode();

    static int _count;

    void addTestToNode(QObject*,QString);
    int run(QString hierarchy, bool mainstyle, int argc, char* argv[], QStringList& arguments);
  protected:
    void setName(QString str);
    QString _name;
    QList<QObject*> _tests; //the tests of this node
    QMap<QString,TestNode> _children; //the child nodes of this node

};

} //namespace qtestext

#endif // QTESTEXT_TESTNODE_H
