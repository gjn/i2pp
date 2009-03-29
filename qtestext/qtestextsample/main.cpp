#include "qtestext.h"
#include <testsamples.h>

int main(int argc, char *argv[])
{
  int nresult = 0;
  nresult += qtestext::TestSuite::getInstance()->run(argc,argv);
  nresult += qtestext::TestSuite::getInstance()->run("*",argc,argv);
  nresult += qtestext::TestSuite::getInstance()->run("",argc,argv);
  nresult += qtestext::TestSuite::getInstance()->run("first",argc,argv);
  nresult += qtestext::TestSuite::getInstance()->run("testing",argc,argv);
  nresult += qtestext::TestSuite::getInstance()->run("testing_*",argc,argv);
  nresult += qtestext::TestSuite::getInstance()->run("testing_sample",argc,argv);
  nresult += qtestext::TestSuite::getInstance()->run("testing_sample_*",argc,argv);
  nresult += qtestext::TestSuite::getInstance()->run("testing_sample_other",argc,argv);
  return nresult;
}
