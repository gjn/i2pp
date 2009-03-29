#include "qtestext.h"
#include <iostream>

int main(int argc, char *argv[])
{
  int nresult = 0;
  int ncount = 0;
  int nDummy;
  //run all tests
  nresult += qtestext::TestSuite::getInstance()->run(nDummy,argc,argv);
  ncount += nDummy;
  std::cout  << "*************************************************************************" << std::endl;
  if (nresult > 0)
    std::cout << nresult << " Failure(s)! (" << ncount << " classes tested)" << std::endl;
  else
    std::cout << "0 Failures (" << ncount << " classes tested)" << std::endl;
  std::cout  << "*************************************************************************" << std::endl;
  return nresult;
}
