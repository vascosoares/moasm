#include <iostream>
#include "prop.h"

class Test {
private:
  size_t val;

public:
  prop<size_t> NumCustomFuncs; 
  prop<const size_t> NumCustomFuncs_readonly 
  { __get__() { return val; } };
  
  Test() : val(100) {}
};

int main() {
  Test test;
  test.NumCustomFuncs = 3;
  std::cout << test.NumCustomFuncs << std::endl;

  size_t x = 4;
  test.NumCustomFuncs = x;
  std::cout << test.NumCustomFuncs << std::endl;

  std::cout << test.NumCustomFuncs++ << std::endl;
  std::cout << ++test.NumCustomFuncs << std::endl;
  std::cout << test.NumCustomFuncs << std::endl;

  test.NumCustomFuncs *= 4;
  std::cout << test.NumCustomFuncs << std::endl;

  //test.NumCustomFuncs_readonly = 100;   // compile error: no operator=
  std::cout << test.NumCustomFuncs_readonly << std::endl;
};
