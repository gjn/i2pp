#ifndef TESTCONTEXT_H
#define TESTCONTEXT_H

#include <QObject>

class TestContext : public QObject
{
  Q_OBJECT
  public:
    TestContext();
  private slots:
    void testConstruction();
};

#endif // TESTCONTEXT_H
