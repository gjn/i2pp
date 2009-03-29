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

    void addTestToNode(QObject*,QString);
    int run(QString hierarchy, int argc, char* argv[]);
    int run(QString hierarchy, QStringList& arguments);
  protected:
    void setName(QString str);
    QString _name;
    QList<QObject*> _list; //the tests of this node
    QMap<QString,TestNode> _children; //the child nodes of this node

};

} //namespace qtestext

#endif // QTESTEXT_TESTNODE_H
