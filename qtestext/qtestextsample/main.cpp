#include "qtestext.h"
#include <iostream>

int main(int argc, char *argv[])
{
  int nresult = 0;
  int ncount = 0;
  int nDummy;
  nresult += qtestext::TestSuite::getInstance()->run(nDummy,argc,argv);
  ncount += nDummy;
  nresult += qtestext::TestSuite::getInstance()->run("*",nDummy,argc,argv);
  ncount += nDummy;
  nresult += qtestext::TestSuite::getInstance()->run("",nDummy,argc,argv);
  ncount += nDummy;
  nresult += qtestext::TestSuite::getInstance()->run("first",nDummy,argc,argv);
  ncount += nDummy;
  nresult += qtestext::TestSuite::getInstance()->run("testing",nDummy,argc,argv);
  ncount += nDummy;
  nresult += qtestext::TestSuite::getInstance()->run("testing_*",nDummy,argc,argv);
  ncount += nDummy;
  nresult += qtestext::TestSuite::getInstance()->run("testing_sample",nDummy,argc,argv);
  ncount += nDummy;
  nresult += qtestext::TestSuite::getInstance()->run("testing_sample_*",nDummy,argc,argv);
  ncount += nDummy;
  nresult += qtestext::TestSuite::getInstance()->run("testing_sample_other",nDummy,argc,argv);
  ncount += nDummy;
  std::cout  << "*************************************************************************" << std::endl;
  if (nresult > 0)
    std::cout << nresult << " Failure(s)! (" << ncount << " classes tested)" << std::endl;
  else
    std::cout << "0 Failures (" << ncount << " classes tested)" << std::endl;
  std::cout  << "*************************************************************************" << std::endl;
  return nresult;
}
