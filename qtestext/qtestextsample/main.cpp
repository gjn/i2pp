#include "qtestext.h"
#include <QtCore/QCoreApplication>

#include <testsamples.h>

//add them to our test suites
QTESTEXT_ADD_TO(TestSample1,first);
QTESTEXT_ADD_TO(TestSample2,testing);
QTESTEXT_ADD_TO(TestSample3,testing_sample);
QTESTEXT_ADD_TO(TestSample4,testing_sample_other);
QTESTEXT_ADD_TO(TestSample5,testing_sample_other);
QTESTEXT_ADD_TO(TestSample6,testing_sample_yetanother);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return qtestext::TestSuite::getInstance()->run(argc,argv);
}
